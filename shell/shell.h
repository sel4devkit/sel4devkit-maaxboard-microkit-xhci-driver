#define SNAKE_NOTIFY 10

struct commands {
    char* keyword;
    char* short_description;
    char* description;
};

struct commands command_list[] = {
    {"disable", "toggle keyboard", "toggle keyboard (can be reenabled with mouse scroll)"},
    {"kbdtest", "enter keyboard test", "Enter keyboard test mode"},
    {"getdev", "print device information", "Usage: Getdev <id>\nGet device info of device <id>"},
    {"history", "display history", "display list of commands"},
    {"init", "display splash", "display splash"},
    {"lsdev", "list all connected devices", "List all devices connected to board"},
    {"mousetest", "enter mouse test", "enter mouse test mode"},
    {"read", "read blocks from connected device", "Usage: read <x> <y>\nRead x blocks starting from block y"},
    {"snake", "play snake", "Play snake"},
    {"write", "write blocks to connected device", "Usage: write <x> <y> <v>\nWrite v (size x blocks) starting from block y"},
};

int no_commands = 10;

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
#define ANSI_BOLD       "\u001b[1m"

#define HEXDUMP(a, b, c) \
    do { \
		hexdump(printf, a, b, c); \
    } while (/*CONSTCOND*/0)

enum states {
    CONSOLE,
    SNAKE,
    MOUSE_TEST,
    KEYBOARD_TEST,
    DISABLED
};

enum states console_state = CONSOLE;