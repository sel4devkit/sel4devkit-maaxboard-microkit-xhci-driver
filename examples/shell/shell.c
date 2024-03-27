/* This work is Crown Copyright NCSC, 2023. */
#include <microkit.h>
#include <shared_ringbuffer/shared_ringbuffer.h>
#include "wsksymdef.h"
#include "wsksymvar.h"
#include <stdint.h>
#include <xhci_api.h>
#include <shell.h>
#include <stdlib.h>
#include <stdio.h>
#include <pdprint.h>
#include <string.h>
#include <ff.h>

// snake globals
char* kbd_buffer;

//rings for notifications
uintptr_t kbd_free;
uintptr_t kbd_used;
uintptr_t mse_free;
uintptr_t mse_used;
uintptr_t uts_free;
uintptr_t uts_used;
uintptr_t umass_resp;
uintptr_t umass_req;
char* keysDown[8];

/* Pointers to shared_ringbuffers */
ring_handle_t *kbd_buffer_ring;
ring_handle_t *mse_buffer_ring;
ring_handle_t *uts_buffer_ring;
blk_queue_handle_t *umass_buffer_ring;

//shell globals
#define MAX_KEYS 6
#define CMD_LIMIT 1024
#define ARGMAX 10
char cmd[CMD_LIMIT];

//shell history globals
#define CMD_HISTORY 1024
static int cursor_index = 0;
static int cmd_len = 0;
char *history[CMD_HISTORY];
static int cmd_hist = -1;
static int cmd_hist_cursor = 0;

//keyboard specifics
uint32_t LAYOUT = KB_UK;
extern const struct wscons_keydesc hidkbd_keydesctab[];
extern const keysym_t hidkbd_keydesc_us[];
extern const keysym_t hidkbd_keydesc_uk[];
#define CODEMASK 0x0ff
#define KC(n)		KS_KEYCODE(n)
void init_mousetest();

// heap(s)
uintptr_t shared_heap;
uintptr_t shared_soft_heap;

// for pdprint
char *pd_name = "shell";

// uts test screen
#define SCREEN_WIDTH	30	/* the virtual screen width */
#define SCREEN_HEIGHT	20	/* the virtual screen height */

#define BORDER_CORNER	'+'	/* character at corners of border */
#define BORDER_VERT		'|'	/* character for vertical border */
#define BORDER_HORI		'-'	/* character for horizontal border */


void print_splash_screen_1(void);
void print_splash_screen_2(void);

void reset_prompt() {
    printf("\n"TERM_OK"seL4 test>>> "ANSI_CLEAR);
}

void
init_shell() {
    print_splash_screen_2();
    console_state = CONSOLE;
    reset_prompt();
}

// function for parsing command words 
size_t split(char *buffer, char *argv[], size_t argv_size)
{
    char *p, *start_of_word;
    int c;
    enum states { DULL, IN_WORD, IN_STRING } state = DULL;
    size_t argc = 0;

    for (p = buffer; argc < argv_size && *p != '\0'; p++) {
        c = (unsigned char) *p;
        switch (state) {
        case DULL:
            if (isspace(c)) {
                continue;
            }

            if (c == '"') {
                state = IN_STRING;
                start_of_word = p + 1; 
                continue;
            }
            state = IN_WORD;
            start_of_word = p;
            continue;

        case IN_STRING:
            if (c == '"') {
                *p = 0;
                argv[argc++] = start_of_word;
                state = DULL;
            }
            continue;

        case IN_WORD:
            if (isspace(c)) {
                *p = 0;
                argv[argc++] = start_of_word;
                state = DULL;
            }
            continue;
        }
    }

    if (state != DULL && argc < argv_size)
        argv[argc++] = start_of_word;

    return argc;
}

void help() {
    for (int i = 0; i < no_commands; i++) {
        printf("%s%*c- %s\n", command_list[i].keyword, 10 - strlen(command_list[i].keyword), ' ', command_list[i].short_description);
    }
    reset_prompt();
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

FATFS *FatFs;

void
decode_command() {
    char *parsedArgs[ARGMAX];

    // set all index to null for error catching
    for (int i = 0; i < ARGMAX; i++) {
        parsedArgs[i] = NULL;
    }

    if (cmd_len > 0) {
        cmd[cmd_len] = '\0';
        char hist[100];
        strncpy(hist, cmd, strlen(cmd));
        split(cmd, parsedArgs, ARGMAX);
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
            printf("\n");
            cursor_index = cmd_len = 0;
            init_mousetest();
            return;
        } else if (!strcmp(parsedArgs[0], "utstest")) {
            console_state = UTS_TEST;
            cmd_hist++;
            history[cmd_hist] = malloc(sizeof(cmd));
            strncpy(history[cmd_hist], hist, strlen(hist));
            cmd_hist_cursor = cmd_hist+1;
            memset(cmd, '\0', sizeof(cmd));
            printf("\n");
            cursor_index = cmd_len = 0;
            init_mousetest();
            return;
        } else if (!strcmp(parsedArgs[0], "read")) {
            // catch invalid arguments
            if (parsedArgs[3] == NULL || parsedArgs[1] == NULL || parsedArgs[2] == NULL || parsedArgs[4] != NULL) { //TODO: get length of devices
                printf("Invalid Args\n");
                printf("Usage: read [devid] [blkno] [nblks]\n");
                reset_prompt();
            } else {
                int blkno = atoi(parsedArgs[2]);
                int nblks = atoi(parsedArgs[3]);
                int blksize = get_blksize(atoi(parsedArgs[1]));
                if (blksize > 0) {
                    char* val = malloc((blksize * nblks));
                    enqueue_umass_request(atoi(parsedArgs[1]), true, blkno, nblks, val, &print_blocks);
                } else {
                    printf("Device %d not mass storage\n", atoi(parsedArgs[1]));
                }
            }
        } else if (!strcmp(parsedArgs[0], "write")) {
            // catch invalid arguments
            if (parsedArgs[4] == NULL || parsedArgs[3] == NULL || parsedArgs[1] == NULL || parsedArgs[2] == NULL || parsedArgs[5] != NULL) {
                printf("Invalid Args\n");
                printf("Usage: write [devid] [blkno] [nblks] [text]\n");
                reset_prompt();
            } else {
                int blkno = atoi(parsedArgs[2]);
                int nblks = atoi(parsedArgs[3]);
                int blksize = get_blksize(atoi(parsedArgs[1]));
                if (blksize > 0) {
                    char* val = malloc((blksize * nblks));
                    printf("size of write %d\n", blksize*nblks);
                    strncpy(val, parsedArgs[4], strlen(parsedArgs[4]));
                    enqueue_umass_request(atoi(parsedArgs[1]), false, blkno, nblks, val, &write_complete);
                } else {
                    printf("Device %d not mass storage\n", atoi(parsedArgs[1]));
                }
            }
        } else if (!strcmp(parsedArgs[0], "fatls")) {
            printf("listing from %s\n", parsedArgs[1]);
            FRESULT res;
            DIR *dir = malloc(sizeof(DIR));
            FILINFO *fno = malloc(sizeof(FILINFO));
            res = f_mount(FatFs, "2", 0);
            int nfile, ndir;
            char *path = parsedArgs[1];

            res = f_opendir(dir, path);                       /* Open the directory */
            if (res == FR_OK) {
                nfile = ndir = 0;
                for (;;) {
                    res = f_readdir(dir, fno);                   /* Read a directory item */
                    if (res != FR_OK || fno->fname[0] == 0) break;  /* Error or end of dir */
                    if (fno->fattrib & AM_DIR) {            /* Directory */
                        printf("   <DIR>   %s\n", fno->fname);
                        ndir++;
                    } else {                               /* File */
                        printf("%10u %s\n", fno->fsize, fno->fname);
                        nfile++;
                    }
                }
                f_closedir(dir);
            } else {
                printf("Failed to open \"%s\". (%u)\n", path, res);
            }
        } else if (!strcmp(parsedArgs[0], "fatread")) {
            char* fileName = parsedArgs[1];
            char *line = malloc(100);
            FIL *fp = malloc(sizeof(FIL));
            BYTE mode = FA_READ;
            FRESULT fr;
            fr = f_mount(FatFs, "2", 0);
            fr = f_open (fp, fileName, mode);
            if (fr) {
                printf("file error %d\n", fr);
            } else {
                printf("======= SOF %s =======\n", fileName);
                while (f_gets(line, sizeof(char) * 100, fp)) {
                    printf("%s\n", line);
                }

                f_close(fp);
                printf("======= EOF %s =======\n", fileName);
            }
        } else if (!strcmp(parsedArgs[0], "fatwrite")) {
            if (parsedArgs[3] != NULL || parsedArgs[1] == NULL || parsedArgs[2] == NULL) {
                printf("Invalid Args\n");
                printf("Usage: fatwrite [filename] [text]\n");
                reset_prompt();
            }
            FIL *file = malloc(sizeof(FIL));
            UINT bw;
            FRESULT fr;
            BYTE mode = FA_WRITE | FA_CREATE_ALWAYS | FA_READ;

            char *fileName = parsedArgs[1];
            printf("writing to file '%s'\n", fileName);
            char *teststr = parsedArgs[2];
            char *buffer = malloc(sizeof(char)*strlen(teststr));
            strncpy(buffer, teststr, strlen(teststr));
            fr = f_mount(FatFs, "2", 0);
            fr = f_open(file, fileName, mode);
            if (fr)
                printf("file error open %d\n", fr);
            fr = f_write(file, buffer, sizeof(char) * strlen(teststr), &bw);
            if (fr)
                printf("file error write %d\n", fr);
            f_close(file);
            printf("wrote %d to file %s\n", bw, fileName);
        } else if (!strcmp(parsedArgs[0], "kbdtest")) {
            printf("\n");
            console_state = KEYBOARD_TEST;
            return;
        } else if (!strcmp(parsedArgs[0], "snake")) {
            *kbd_buffer = 'c';
            printf("set kbd_buffer to %c %p\n", *kbd_buffer, kbd_buffer);
            console_state = SNAKE;
            microkit_notify(SNAKE_NOTIFY);
        } else if (!strcmp(parsedArgs[0], "getdev")) {
            print_device(atoi(parsedArgs[1]));
        } else if (!strcmp(parsedArgs[0], "lsdev")) {
            print_devs();
        } else if (!strcmp(parsedArgs[0], "help") || !strcmp(parsedArgs[0], "?")) {
            help();
        } else {
            printf("%s is not a recognised command!\n", parsedArgs[0]);
        }
        cmd_hist++;
        history[cmd_hist] = malloc(sizeof(hist));
        strncpy(history[cmd_hist], hist, strlen(hist));
        cmd_hist_cursor = cmd_hist+1;
        memset(cmd, '\0', sizeof(cmd));
        printf("\n");
    }
    reset_prompt();
    cursor_index = cmd_len = 0;
}

void clear_prompt() {
    printf("\r"TERM_OK"seL4 test>>> "ANSI_CLEAR);
    for (int i = 0; i <= strlen(cmd); i++) {
        printf(" ");
    }
    printf("\r"TERM_OK"seL4 test>>> "ANSI_CLEAR);
}

void
scroll_hist(int direction) {
    if ((cmd_hist_cursor <= 0) && direction <= -1)
        return;
    clear_prompt();
    if (cmd_hist_cursor + direction <= cmd_hist && cmd_hist_cursor + direction >= 0) {
        cmd_hist_cursor+=direction;
        strncpy(cmd, history[cmd_hist_cursor], strlen(history[cmd_hist_cursor]));
    } else {
        cmd_hist_cursor = cmd_hist+1;
        strncpy(cmd, "", sizeof(""));
    }
    cmd_len = cursor_index = strlen(cmd);
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
    }
}
void
handle_utsEvent()
{
    uintptr_t *buffer = 0;
    unsigned int len = 0;
    void *cookie = NULL;

    int index;
    while (!driver_dequeue(uts_buffer_ring->used_ring, (uintptr_t*)&buffer, &len, &cookie)) {
        printf("%c%c%c%c%c%c\r", 61707,61707,61707,61707,61707,61707);
        printf("x: %04d\n", buffer[0]);
        printf("y: %04d\n", buffer[1]);
        printf("z: %04d\n", buffer[2]);
        if (buffer[3] & 0x1)
            printf("left ");
        if (buffer[3] & 0x2)
            printf("mid ");
        if (buffer[3] & 0x4)
            printf("right ");
        printf("                ");
        printf("\n\n\n");
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
        if (((char *) buffer)[2] == 0x1)
            break; //too many keys pressed

        //get unique keypress (NOTE: does not handle unique release)
        uint8_t keyPressed;
        int unique_id = -1;
        int temp_unique_id = -1;
        for (int i = 2; i < MAX_KEYS+2; i++) {
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
        keyPressed = (uint8_t)((char*)buffer)[unique_id];

        //update previous buffer
        for (int i = 2; i < MAX_KEYS+2; i++) {
            keysDown[i] = ((char*)buffer)[i];
        }
        // stop processing on all keys released
        if (keyPressed == 0)
            break;

        // decode keycode from hex
        // first byte is 0x01 for Ctrl, 0x02 for Shft
        uint8_t shiftOrControl = ((char *) buffer)[0];
        int lowercaseAdd = shiftOrControl == 0 ? 1 : 0; // If shift or control held then want to add that value only
        index = 0;
        keysym_t keypress;
        for (int i = 0; i < 304; i++) {
            switch (LAYOUT) {
                case KB_UK:
                    if (hidkbd_keydesc_uk[i] == KC(keyPressed&CODEMASK)) {
                        index = i;
                        keypress = hidkbd_keydesc_uk[i + lowercaseAdd + shiftOrControl];
                        break;
                    }
                case KB_US:
                default:
                    if (hidkbd_keydesc_us[i] == KC(keyPressed&CODEMASK)) {
                        index = i;
                        keypress = hidkbd_keydesc_us[i + lowercaseAdd + shiftOrControl];
                    }
                    break;
            }
            if (index > 0)
                break;
        }
        if (index == 0)
            keypress = hidkbd_keydesc_us[index + lowercaseAdd + shiftOrControl];
        switch (console_state) {
            case SNAKE:
                *kbd_buffer = keypress;
                break;
            case CONSOLE:
                if (keyPressed == 0)
                    break;
                int ofs = 0;
                int i;
                switch(keypress) {
                    case KS_BackSpace:
                        if (cursor_index > 0) {
                            printf("%c %c", keypress, keypress);
                            cursor_index--;
                            cmd_len--;
                            if (cursor_index != cmd_len) {
                                for(i = cursor_index; i < (cmd_len); i++) {
                                    cmd[i] = cmd[i+1];
                                    ofs++;
                                    printf("%c", cmd[i]);
                                }
                                printf(" ");
                                for (i = 0; i <= ofs; i++) {
                                    printf("\b");
                                }
                            }
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
                    case KS_Left:
                        if (cursor_index > 0) {
                            printf("\b");
                            cursor_index--;
                        }
                        break;
                    case KS_Right:
                        if (cursor_index < cmd_len) {
                            printf("%c", cmd[cursor_index]);
                            cursor_index++;
                        }
                        break;
                    default:
                        if (cursor_index < CMD_LIMIT) {
                            if ((keypress >= KS_space && keypress <= KS_z)) {
                                printf("%c", keypress);
                                if (cursor_index != cmd_len) {
                                    for (i = cmd_len; i >= cursor_index; i--) {
                                        ofs++;
                                        cmd[i+1] = cmd[i];
                                    }
                                    for (i = cursor_index+1; i < cmd_len+1; i++) {
                                        printf("%c", cmd[i]);
                                    }
                                    for (i = 0; i < ofs-1; i++) {
                                        printf("\b");
                                    }
                                }
                                cmd_len++;
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
                break;
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
    }
}

void
init(void) {
    api_init(&kbd_buffer_ring, &mse_buffer_ring, &uts_buffer_ring, &umass_buffer_ring);
    FatFs = malloc(sizeof(*FatFs));
    FRESULT fr = f_mount(FatFs, "2", 0); // mount usb device (id 2)
    if (fr) {
        print_warn("mount error %d\n", fr);
    }
    else {
        print_info("Mounted USB succesfully\n");
    }

    print_info("Initialised\n");
}

void
notified(microkit_channel ch) {
    switch(ch) {
/* ----------------API NOTIFICATIONS---------- */
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
        case TOUCHSCREEN_EVENT:
            if (console_state == UTS_TEST)
                handle_utsEvent();
            break;
        case NEW_DEVICE_EVENT:
            handle_new_device();
            break;
        case INIT:
            cmd_hist_cursor = 0;
            cmd_hist = -1;
            init_shell();
            break;
/* ---------------------------------------- */
        case SNAKE_NOTIFY:
            console_state = CONSOLE;
            clear_prompt();
            break;
        default:
            print_warn("Unexpected channel %d\n", ch);
    }
}

void print_splash_screen_1(void) {
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
    printf("                                                                    \n");
}

void print_splash_screen_2(void) {
    printf("                                                         $$$$$$                         \n");
    printf("                                                         $$$$$$             $$$$$$      \n");
    printf("        $$$$$$$$$$$$                                     $$$$$$           $$$$$$$$      \n");
    printf("     $$$$$$$$$$$$$$$$$$         $$$$$$$$$    $$$$$$$$    $$$$$$          $$$$$$$$$      \n");
    printf("   $$$$$$$$$$$$$$$$$$$$$$      $$$$   $$$$  $$$$  $$$$   $$$$$$        $$$$$$$$$$$      \n");
    printf("  $$$$$$$$$$$$$$$$$$$$$$$$      $$$$$       $$$$$$$$$$   $$$$$$      $$$$$  $$$$$$      \n");
    printf(" $$$$$$$$$$$$$$$$$$$$$$$$$$         $$$$$   $$$$         $$$$$$    $$$$$    $$$$$$      \n");
    printf("$$$$$$$    $$$$$$$$$$$$$$$$$   $$$$   $$$$  $$$$  $$$$   $$$$$$$  $$$$$     $$$$$$      \n");
    printf("$$$$$$      $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   \n");
    printf("$$$$$$      $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   \n");
    printf("$$$$$$$    $$$$$$$$$$$$$$$$$         _____ __  __________    __             $$$$$$      \n");
    printf(" $$$$$$$$$$$$$$$$$$$$$$$$$$         / ___// / / / ____/ /   / /             $$$$$$      \n");
    printf("  $$$$$$$$$$$$$$$$$$$$$$$$          \\__ \\/ /_/ / __/ / /   / /                          \n");
    printf("   $$$$$$$$$$$$$$$$$$$$$$          ___/ / __  / /___/ /___/ /___                        \n");
    printf("     $$$$$$$$$$$$$$$$$$           /____/_/ /_/_____/_____/_____/                        \n");
    printf("        $$$$$$$$$$$$                                                                    \n");
    printf("                                                                                        \n");
    printf("                                                                                        \n");
}
