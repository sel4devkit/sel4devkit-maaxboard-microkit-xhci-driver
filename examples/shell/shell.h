// keycode defs
#include "wsksymdef.h"
#include <stdio.h> 
#include <stdlib.h>
#include <microkit.h>
typedef unsigned short keysym_t;

#define SNAKE_NOTIFY 10

struct commands {
    char* keyword;
    char* short_description;
    char* description;
};

struct commands command_list[] = {
    {"disable", "toggle keyboard", "toggle keyboard (can be reenabled with mouse scroll)"},
    {"kbdtest", "enter keyboard test", "Enter keyboard test mode"},
    {"fatls", "list files at filepath", "Usage: fatls <devid> <filepath>"},
    {"fatread", "read file", "Usage: fatread <devid> <filepath>"},
    {"fatwrite", "write file", "Usage: fatwrite <devid> <filepath> <value>"},
    {"getdev", "print device information", "Usage: Getdev <id>\nGet device info of device <id>"},
    {"history", "display history", "display list of commands"},
    {"init", "display splash", "display splash"},
    {"lsdev", "list all connected devices", "List all devices connected to board"},
    {"mousetest", "enter mouse test", "enter mouse test mode"},
    {"read", "read blocks from connected device", "Usage: read <x> <y>\nRead x blocks starting from block y"},
    {"snake", "play snake", "Play snake"},
    {"write", "write blocks to connected device", "Usage: write <x> <y> <v>\nWrite v (size x blocks) starting from block y"},
};

int no_commands = 13;

//! should get this from device information, hardcoded for now
#define SECTOR_SIZE 512

#define ANSI_RED		"\x1b[1;31m"
#define ANSI_GREEN		"\x1b[1;32m"
#define ANSI_YELLOW		"\x1b[1;33m"
#define ANSI_BLUE		"\x1b[1;34m"
#define ANSI_WHITE		"\x1b[1;37m"
#define ANSI_CLEAR		"\x1b[0m"
#define TERM_OK         "\x1b[32;1m"
#define TERM_ERR        "\x1b[31;1m"

#define HEXDUMP(a, b, c) \
    do { \
		hexdump(printf, a, b, c); \
    } while (/*CONSTCOND*/0)

enum states {
    CONSOLE,
    SNAKE,
    MOUSE_TEST,
    KEYBOARD_TEST,
    UTS_TEST,
    DISABLED
};

enum states console_state = CONSOLE;

#define kmem_zalloc(size, km_flag_t) calloc(1, size);
#define kmem_alloc(size, km_flag_t) malloc(size);
#define kmem_free(addr, size_t) free(addr);

/* Setup for getting printf functionality working */
static int
libc_microkit_putc(char c, FILE *file)
{
    (void) file; /* Not used by us */
    microkit_dbg_putc(c);
    return c;
}

static int
sample_getc(FILE *file)
{
	return -1; /* getc not implemented, return EOF */
}
static FILE __stdio = FDEV_SETUP_STREAM(libc_microkit_putc,
                    sample_getc,
                    NULL,
                    _FDEV_SETUP_WRITE);
FILE *const stdin = &__stdio; __strong_reference(stdin, stdout); __strong_reference(stdin, stderr);
