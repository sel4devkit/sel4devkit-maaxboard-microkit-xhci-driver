/* This work is Crown Copyright NCSC, 2023. */
#include <microkit.h>
#include <printf.h>
#include <shared_ringbuffer.h>
#include <tinyalloc.h>
#include <lib/libkern/libkern.h>
#include <pdprint.h>
#include <sys/kmem.h>
#include <api.h>

#include <dev/wscons/wsksymdef.h>

#define INIT  44

//rings for notifications
uintptr_t rx_free;
uintptr_t rx_used;
uintptr_t mse_free;
uintptr_t mse_used;

/* Pointers to shared_ringbuffers */
ring_handle_t *kbd_buffer_ring;
ring_handle_t *mse_buffer_ring;

//shell globals
#define MAX_KEYS 256
#define CMD_LIMIT 1024
#define ARGMAX 10
char cmd[CMD_LIMIT];

//shell history globals
#define CMD_HISTORY 1024
static int cursor_index = 0;
char *history[CMD_HISTORY];
static int cmd_hist = 0;

//keyboard specifics
extern const keysym_t hidkbd_keydesc_us[];
extern const keysym_t hidkbd_keydesc_uk[];
#define CODEMASK 0x0ff
#define KC(n)		KS_KEYCODE(n)
bool kbd_enabled = false;

// heap
uintptr_t heap_base;
uintptr_t other_heap_base;

//heap specific globals
char* kbd_mem_write;
uintptr_t ta_limit;
uint64_t heap_size = 0x2000000;
int ta_blocks = 1024;
int ta_thresh = 16;
int ta_align = 64;

// for pdprint
char *pd_name = "shell";

/* #define alloc(x) kmem_alloc(x, 0) */
#define alloc(x) ta_alloc(x)

void
init_shell() {
    printf("                                                                                 \n");
    printf("                                                                                 \n");
    printf("    .d8888. d88888b db        j88D    .d8888. db   db d88888b db      db         \n");
    printf("    88'  YP 88'     88       j8~88    88'  YP 88   88 88'     88      88         \n");
    printf("    `8bo.   88ooooo 88      j8' 88    `8bo.   88ooo88 88ooooo 88      88         \n");
    printf("      `Y8b. 88~~~~~ 88      V88888D     `Y8b. 88~~~88 88~~~~~ 88      88         \n");
    printf("    db   8D 88.     88booo.     88    db   8D 88   88 88.     88booo. 88booo.    \n");
    printf("    `8888Y' Y88888P Y88888P     VP    `8888Y' YP   YP Y88888P Y88888P Y88888P    \n");
    printf("                                                                                 \n");
    printf("                                                                                 \n");
    printf("                  dD  .d8b.  db      d8888b. db   db  .d8b.  Cb                  \n");
    printf("                d8'  d8' `8b 88      88  `8D 88   88 d8' `8b  `8b                \n");
    printf("               d8    88ooo88 88      88oodD' 88ooo88 88ooo88    8b               \n");
    printf("              C88    88~~~88 88      88~~~   88~~~88 88~~~88    88D              \n");
    printf("               V8    88   88 88booo. 88      88   88 88   88    8P               \n");
    printf("                V8.  YP   YP Y88888P 88      YP   YP YP   YP  .8P                \n");
    printf("                  VD                                         CP                  \n");
    printf("                                                                                 \n");
    printf("                                                                                 \n");
    kbd_enabled = true;
    printf("\nseL4 test>>> ");
}

// function for parsing command words 
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < ARGMAX; i++) { 
        parsed[i] = strsep(&str, " "); 
        // printf("new arg:%s\n", parsed[i]);
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 

void
decode_command() {
    char *parsedArgs[ARGMAX];
    if (cursor_index > 0) {
        cmd[cursor_index] = '\0';
        parseSpace(cmd, parsedArgs);
        if (!strcmp(parsedArgs[0], "init")) {
            init_shell();
        } else if (!strcmp(parsedArgs[0], "disable")) {
            if (kbd_enabled) {
                kbd_enabled = false;
                printf("keyboard disabled!!!\n");
            } else {
                kbd_enabled = true;
                printf("keyboard enabled!!!\n");
            }
        } else {
            printf("%s is not a recognised command!\n", parsedArgs[0]);
        }
        history[cmd_hist] = cmd;
        cmd_hist++;
        memset(cmd, '\0', sizeof(cmd));
        printf("\n");
    }
    printf("seL4 test>>> ");
    cursor_index = 0;
}

static void 
handle_mouseEvent()
{
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    while (!driver_dequeue(mse_buffer_ring->used_ring, (uintptr_t**)&buffer, &len, &cookie)) {
        printf("MOUSE EVENT: 0x%08x\n", buffer[0]);
    }
}

static void 
handle_keypress()
{
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    while (!driver_dequeue(kbd_buffer_ring->used_ring, (uintptr_t**)&buffer, &len, &cookie)) {
        uint8_t keyPressed = ((char *) buffer)[2];
        if (keyPressed == 0)
            break;
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
            default:
                if (cursor_index < CMD_LIMIT) {
                    if (keypress >= KS_a && keypress <= KS_z || keypress >= KS_A && keypress <= KS_Z || keypress >= KS_0 && keypress <= KS_9 || keypress == KS_space) {
                        if (keypress == KS_space)
                            keypress = ' ';
                        printf("%c", keypress);
                        cmd[cursor_index] = keypress;
                        cursor_index++;
                    }
                }
        }
    }
}

void
init(void) {
    ta_limit = heap_base + heap_size;
    bool error = ta_init((void*)heap_base, (void*)ta_limit, ta_blocks, ta_thresh, ta_align);
    if (!error) {
        print_fatal("Heap initialisation failure %d\n", error);
        return 0;
    }
    kbd_buffer_ring = alloc(sizeof(*kbd_buffer_ring));
    ring_init(kbd_buffer_ring, (ring_buffer_t *)rx_free, (ring_buffer_t *)rx_used, NULL, 0);
    mse_buffer_ring = alloc(sizeof(*mse_buffer_ring));
    ring_init(mse_buffer_ring, (ring_buffer_t *)mse_free, (ring_buffer_t *)mse_used, NULL, 0);
    print_info("Initialised\n");
}

void
notified(microkit_channel ch) {
    switch(ch) {
        case INIT:
            init_shell();
            break;
        case 45:
            if (kbd_enabled)
                handle_keypress();
            break;
        case 46:
            handle_mouseEvent();
            printf("received Mouse event (what do you want me to do with this)\n");
            break;
        default:
            printf("SHELL: Unexpected channel %d\n", ch);
    }
}
