/* This work is Crown Copyright NCSC, 2023. */
#include <microkit.h>
#include <printf.h>
#include <shared_ringbuffer.h>
#include <tinyalloc.h>
#include <lib/libkern/libkern.h>
#include <pdprint.h>
#include <sys/kmem.h>
#include <xhci_api.h>

// keycode defs
#include <dev/wscons/wsksymdef.h>

#define HEXDUMP(a, b, c) \
    do { \
		hexdump(printf, a, b, c); \
    } while (/*CONSTCOND*/0)

// snake globals
char* kbd_buffer;

enum states {
    CONSOLE,
    SNAKE,
    MOUSE_TEST,
    KEYBOARD_TEST,
    DISABLED
};

enum states console_state = CONSOLE;

//rings for notifications
uintptr_t rx_free;
uintptr_t rx_used;
uintptr_t mse_free;
uintptr_t mse_used;
uintptr_t umass_req_free;
uintptr_t umass_req_used;
char* keysDown[8];

/* Pointers to shared_ringbuffers */
ring_handle_t *kbd_buffer_ring;
ring_handle_t *mse_buffer_ring;
ring_handle_t *umass_buffer_ring;

//shell globals
#define MAX_KEYS 256
#define CMD_LIMIT 1024
#define ARGMAX 10
char cmd[CMD_LIMIT];
static bool kbd_no_press = false;

//shell history globals
#define CMD_HISTORY 1024
static int cursor_index = 0;
char *history[CMD_HISTORY];
static int cmd_hist = -1;
static int cmd_hist_cursor = 0;

//keyboard specifics
extern const keysym_t hidkbd_keydesc_us[];
extern const keysym_t hidkbd_keydesc_uk[];
#define CODEMASK 0x0ff
#define KC(n)		KS_KEYCODE(n)
void init_mousetest();

// heap(s)
uintptr_t heap_base;
uintptr_t other_heap_base;

//heap specific globals
uintptr_t ta_limit;
uint64_t heap_size = 0x2000000;
int ta_blocks = 1024;
int ta_thresh = 16;
int ta_align = 64;

// for pdprint
char *pd_name = "shell";

//! should get this from device information, hardcoded for now
#define SECTOR_SIZE 512

/* #define alloc(x) kmem_alloc(x, 0) */
#define alloc(x) ta_alloc(x)

// from apple open source library
int
atoi(const char *in)
{
	char *c;
	int ret;

	ret = 0;
	c = __UNCONST(in);
	if (*c == '-')
		c++;
	for (; isdigit(*c); c++)
		ret = (ret * 10) + (*c - '0');

	return (*in == '-') ? -ret : ret;
}


#define ANSI_RED		"\x1b[1;31m"
#define ANSI_GREEN		"\x1b[1;32m"
#define ANSI_YELLOW		"\x1b[1;33m"
#define ANSI_BLUE		"\x1b[1;34m"
#define ANSI_WHITE		"\x1b[1;37m"
#define ANSI_CLEAR		"\x1b[0m"

void
init_shell() {
    umass_api_init();

    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("        "ANSI_RED"  .d8888. "ANSI_CLEAR" db   db "ANSI_RED" d88888b "ANSI_CLEAR" db      "ANSI_RED" db        j88D "ANSI_CLEAR"           \n");
    printf("        "ANSI_RED"  88'  YP "ANSI_CLEAR" 88   88 "ANSI_RED" 88'     "ANSI_CLEAR" 88      "ANSI_RED" 88       j8~88 "ANSI_CLEAR"           \n");
    printf("        "ANSI_RED"  `8bo.   "ANSI_CLEAR" 88ooo88 "ANSI_RED" 88ooooo "ANSI_CLEAR" 88      "ANSI_RED" 88      j8' 88 "ANSI_CLEAR"           \n");
    printf("        "ANSI_RED"    `Y8b. "ANSI_CLEAR" 88~~~88 "ANSI_RED" 88~~~~~ "ANSI_CLEAR" 88      "ANSI_RED" 88      V88888D"ANSI_CLEAR"           \n");
    printf("        "ANSI_RED"  db   8D "ANSI_CLEAR" 88   88 "ANSI_RED" 88.     "ANSI_CLEAR" 88booo. "ANSI_RED" 88booo.     88 "ANSI_CLEAR"           \n");
    printf("        "ANSI_RED"  `8888Y' "ANSI_CLEAR" YP   YP "ANSI_RED" Y88888P "ANSI_CLEAR" Y88888P "ANSI_RED" Y88888P     VP "ANSI_CLEAR"           \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("            dD  .d8b.  db      d8888b. db   db  .d8b.  Cb           \n");
    printf("          d8'  d8' `8b 88      88  `8D 88   88 d8' `8b  `8b         \n");
    printf("         d8    88ooo88 88      88oodD' 88ooo88 88ooo88    8b        \n");
    printf("        C88    88~~~88 88      88~~~   88~~~88 88~~~88    88D       \n");
    printf("         V8    88   88 88booo. 88      88   88 88   88    8P        \n");
    printf("          V8.  YP   YP Y88888P 88      YP   YP YP   YP  .8P         \n");
    printf("           VD                                         CP            \n");
    printf("                                                                    \n");
    printf("                                                                    \n");NSI_RED, ANSI_CLEAR, ANSI_RED, ANSI_CLEAR, ANSI_RED, ANSI_CLEAR, ANSI_RED, ANSI_CLEAR)
    console_state = CONSOLE;
    printf("\nseL4 test>>> ");
}

// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < ARGMAX; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 

void reset_prompt() {
    printf("\nseL4 test>>> ");
}

//callback for read
void print_blocks(struct umass_request *xfer) {
    HEXDUMP("read", xfer->val, (SECTOR_SIZE * xfer->nblks));
    reset_prompt();
}

//callback for write
void write_complete(struct umass_request *xfer) {
    printf("\nWrite complete\n");
    reset_prompt();
}

void
decode_command() {
    char *parsedArgs[ARGMAX];

    // set all index to null for error catching
    for (int i = 0; i < ARGMAX; i++) {
        parsedArgs[i] = NULL;
    }

    if (cursor_index > 0) {
        cmd[cursor_index] = '\0';
        parseSpace(cmd, parsedArgs);
        if (!strcmp(parsedArgs[0], "init")) {
            init_shell();
        } else if (!strcmp(parsedArgs[0], "disable")) {
            if (console_state != DISABLED) {
                console_state = DISABLED;
                printf("keyboard disabled!!!\n");
            } else {
                console_state = CONSOLE;
                printf("keyboard enabled!!!\n");
            }
        } else if (!strcmp(parsedArgs[0], "history")) {
            printf("cmd_hist %d\n", cmd_hist);
            for (int c = 0; c < cmd_hist; c++) {
                printf("hist %d: %s\n", c, history[c]);
            }
        
        } else if (!strcmp(parsedArgs[0], "mousetest")) {
            console_state = MOUSE_TEST;
            cmd_hist++;
            history[cmd_hist] = kmem_alloc(sizeof(cmd),0);
            strncpy(history[cmd_hist], cmd, sizeof(cmd));
            cmd_hist_cursor = cmd_hist+1;
            memset(cmd, '\0', sizeof(cmd));
            printf("\n");
            cursor_index = 0;
            init_mousetest();
            return;
        } else if (!strcmp(parsedArgs[0], "read")) {
            // catch invalid arguments
            if (parsedArgs[3] != NULL || parsedArgs[1] == NULL || parsedArgs[2] == NULL | parsedArgs[2] < 1) {
                printf("Invalid Args\n");
                printf("Usage: read [blkno] [nblks]\n");
                reset_prompt();
            } else {
                int blkno = atoi(parsedArgs[1]);
                int nblks = atoi(parsedArgs[2]);
                char* val = kmem_alloc((SECTOR_SIZE * nblks), 0);
                enqueue_umass_request(0 ,true, blkno, nblks, val, &print_blocks);
            }
        } else if (!strcmp(parsedArgs[0], "write")) {
            // catch invalid arguments
            if (parsedArgs[3] == NULL || parsedArgs[1] == NULL || parsedArgs[2] == NULL || parsedArgs[4] != NULL) {
                printf("Invalid Args\n");
                printf("Usage: write [blkno] [nblks] [text]\n");
                reset_prompt();
            } else {
                int blkno = atoi(parsedArgs[1]);
                int nblks = atoi(parsedArgs[2]);
                char* val = kmem_alloc((SECTOR_SIZE * nblks), 0);
                strncpy(val, parsedArgs[3], sizeof(parsedArgs[3]));
                enqueue_umass_request(0 ,false, blkno, nblks, val, &write_complete);
            }
        } else if (!strcmp(parsedArgs[0], "rw")) {
            char* val2 = kmem_alloc((SECTOR_SIZE * 1), 0);
            char* val = kmem_alloc((SECTOR_SIZE * 8), 0);
            strncpy(val, parsedArgs[1], sizeof(parsedArgs[1]));
            enqueue_umass_request(0 ,false, 1, 8, val, &write_complete);
            printf("between\n");
            enqueue_umass_request(0 ,true, 1, 1, val2, &print_blocks);
        } else if (!strcmp(parsedArgs[0], "kbdtest")) {
            printf("\n");
            console_state = KEYBOARD_TEST;
            return;
        } else if (!strcmp(parsedArgs[0], "snake")) {
            *kbd_buffer = 'c';
            printf("set kbd_buffer to %c %p\n", *kbd_buffer, kbd_buffer);
            console_state = SNAKE;
            microkit_notify(10);
        } else {
            printf("%s is not a recognised command!\n", parsedArgs[0]);
        }
        cmd_hist++;
        history[cmd_hist] = kmem_alloc(sizeof(cmd),0);
        strncpy(history[cmd_hist], cmd, sizeof(cmd));
        cmd_hist_cursor = cmd_hist+1;
        memset(cmd, '\0', sizeof(cmd));
        printf("\n");
    }
    reset_prompt();
    cursor_index = 0;
}

void clear_prompt() {
    printf("\rseL4 test>>>");
    for (int i = 0; i <= strlen(cmd); i++) {
        printf(" ");
    }
    printf("\rseL4 test>>> ");
}

void
scroll_hist(int direction) {
    if ((cmd_hist_cursor <= 0) && direction <= -1)
        return;
    clear_prompt();
    if (cmd_hist_cursor + direction <= cmd_hist && cmd_hist_cursor + direction >= 0) {
        cmd_hist_cursor+=direction;
        strncpy(cmd, history[cmd_hist_cursor], sizeof(history[cmd_hist_cursor]));
    } else {
        strncpy(cmd, "", sizeof(""));
    }
    cursor_index = strlen(cmd);
    printf("%s", cmd);
}

void
init_mousetest() {
    printf("\n");
    printf("\n");
    printf("x: %04d\n", 0);
    printf("y: %04d\n", 0);
    printf("w: %04d\n", 0);
    printf("\n\n\n");
}

void
handle_mouseTest()
{
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    while (!driver_dequeue(mse_buffer_ring->used_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        printf("%c%c%c%c%c%c\r", 61707,61707,61707,61707,61707,61707);
        printf("x: %04d\n", buffer[0]);
        printf("y: %04d\n", buffer[1]);
        printf("w: %04d\n", buffer[2]);
        if (buffer[4] & 0x1)
            printf("left ");
        if (buffer[4] & 0x2)
            printf("mid ");
        if (buffer[4] & 0x4)
            printf("right ");
        printf("                ");
        printf("\n\n\n");
        kmem_free(buffer, sizeof(buffer));
    }
}

static void 
handle_mouseEvent()
{
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    while (!driver_dequeue(mse_buffer_ring->used_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        if ((int)buffer[2] <= -1) {
            scroll_hist(-1);
        } else if ((int)buffer[2] >= 1) {
            scroll_hist(1);
        }
        kmem_free(buffer, sizeof(buffer));
    }
}

static void 
handle_keypress()
{
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    while (!driver_dequeue(kbd_buffer_ring->used_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        //get unique keypress
        uint8_t keyPressed;
        int unique_id = -1;
        int temp_unique_id = -1;
        if (((char *) buffer)[2] != 0x1) {
            for (int i = 2; i < 8; i++) {
                if (((char*)buffer)[i] != 0x0) {
                    for (int j = 2; j < 8; j++) {
                        if (((char*)buffer)[i] == keysDown[j]) {
                            temp_unique_id = -1;
                            break;
                        }
                        temp_unique_id = i;
                    }
                    if (temp_unique_id != -1)
                        unique_id = temp_unique_id;
                }
            }
            keyPressed = ((char*)buffer)[unique_id];

            //update previous buffer
            keysDown[2] = ((char*)buffer)[2];
            keysDown[3] = ((char*)buffer)[3];
            keysDown[4] = ((char*)buffer)[4];
            keysDown[5] = ((char*)buffer)[5];
            keysDown[6] = ((char*)buffer)[6];
            keysDown[7] = ((char*)buffer)[7];
        } else {
            //too many keys pressed
            break;
        }
        // stop processing on all keys released
        if (keyPressed == 0)
            break;

        // decode keycode from hex
        // first byte is 0x01 for Ctrl, 0x02 for Shft
        uint8_t shiftOrControl = ((char *) buffer)[0];
        int lowercaseAdd = shiftOrControl == 0 ? 1 : 0; // If shift or control held then want to add that value only
        index = 0;
        for (int i = 0; i < 274; i++) {
            if (hidkbd_keydesc_us[i] == KC(keyPressed&CODEMASK)) {
                index = i;
                break;
            }
        }
        keysym_t keypress = hidkbd_keydesc_us[index + lowercaseAdd + shiftOrControl];
        switch (console_state) {
            case SNAKE:
                *kbd_buffer = keypress;
                break;
            case CONSOLE:
                if (keyPressed == 0)
                    break;
                switch(keypress) {
                    case KS_BackSpace:
                        if (cursor_index > 0) {
                            printf("%c %c", keypress, keypress);
                            cursor_index--;
                        }
                        break;
                    case KS_Return:
                        printf("\n");
                        decode_command();
                        break;
                    case KS_Up:
                        scroll_hist(-1);
                        break;
                    case KS_Down:
                        scroll_hist(1);
                        break;
                    default:
                        if (cursor_index < CMD_LIMIT) {
                            if ((keypress >= KS_a && keypress <= KS_z) || (keypress >= KS_A && keypress <= KS_Z) || (keypress >= KS_0 && keypress <= KS_9) || keypress == KS_space) {
                                printf("%c", keypress);
                                cmd[cursor_index] = keypress;
                                cursor_index++;
                            }
                        }
                }
                break;
            case MOUSE_TEST:
                if (buffer[0] & 0x01 && keypress == KS_c) {
                    console_state = CONSOLE;
                    printf("\nEnd of mouse test\n");
                    clear_prompt();
                }
            case KEYBOARD_TEST:
                printf("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n", ((char*)buffer)[0], ((char*)buffer)[1], ((char*)buffer)[2], ((char*)buffer)[3], ((char*)buffer)[4], ((char*)buffer)[5]);
                printf("\r");
                printf("\x1b[s"); /* save current cursor position */
                printf("%*s", 30, ""); /* blank out virual screen */
                printf("\x1b[u"); /* move cursor back to saved position */
                break;
            default:
                print_fatal("Unrecognised keyboard state\n");
        }
        kmem_free(buffer, sizeof(buffer));
    }
}

void
init(void) {
    ta_limit = heap_base + heap_size;
    bool status = ta_init((void*)heap_base, (void*)ta_limit, ta_blocks, ta_thresh, ta_align);
    if (!status) {
        print_fatal("Heap initialisation failure %d\n", status);
        return 0;
    }
    kbd_buffer_ring = alloc(sizeof(*kbd_buffer_ring));
    ring_init(kbd_buffer_ring, (ring_buffer_t *)rx_free, (ring_buffer_t *)rx_used, NULL, 0);
    mse_buffer_ring = alloc(sizeof(*mse_buffer_ring));
    ring_init(mse_buffer_ring, (ring_buffer_t *)mse_free, (ring_buffer_t *)mse_used, NULL, 0);
    umass_buffer_ring = alloc(sizeof(*umass_buffer_ring));
    ring_init(umass_buffer_ring, (ring_buffer_t *)umass_req_free, (ring_buffer_t *)umass_req_used, NULL, 0);
    print_info("Initialised\n");
}

void
notified(microkit_channel ch) {
    switch(ch) {
        case INIT:
            cmd_hist_cursor = 0;
            cmd_hist = -1;
            init_shell();
            break;
        case KEYBOARD_EVENT:
            if (console_state != DISABLED)
                handle_keypress();
            break;
        case MOUSE_EVENT:
            if (console_state == MOUSE_TEST)
                handle_mouseTest();
            else
                handle_mouseEvent();
            break;
        case UMASS_COMPLETE:
            handle_xfer_complete();
            break;
        case 10:
            console_state = CONSOLE;
            clear_prompt();
            break;
        default:
            print_warn("Unexpected channel %d\n", ch);
    }
}
