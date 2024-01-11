/* This work is Crown Copyright NCSC, 2023. */
#include <microkit.h>
#include <pdprint.h>
#include <lib/libkern/libkern.h>
#include <stdlib.h>
#include <stdio.h>

extern uintptr_t __heap_start;
extern uintptr_t __heap_end;

// Setup for getting printf functionality working {{{
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
// END OF LIBC
// }}}

uintptr_t heap_base;
uintptr_t fdt;
uint64_t heap_size = 0x2000000;
int ta_blocks = 2048;
int ta_thresh = 16;
int ta_align = 64;
uintptr_t ta_limit;
#define STR2(x) #x
#define STR(x) STR2(x)
 
#define INCBIN_SECTION ".rodata"
char *pd_name = "mem_handler";
 
// this aligns start address to 16 and terminates byte array with explict 0
// which is not really needed, feel free to change it to whatever you want/need
#define INCBIN(name, file) \
    __asm__(".section " INCBIN_SECTION "\n" \
            ".global incbin_" STR(name) "_start\n" \
            ".balign 16\n" \
            "incbin_" STR(name) "_start:\n" \
            ".incbin \"" file "\"\n" \
            \
            ".global incbin_" STR(name) "_end\n" \
            ".balign 1\n" \
            "incbin_" STR(name) "_end:\n" \
            ".byte 0\n" \
    ); \
    extern __attribute__((aligned(16))) const char incbin_ ## name ## _start[]; \
    extern                              const char incbin_ ## name ## _end[]

int test1 = 12;
INCBIN(device_tree, "kernel/kernel.bin");
int test2 = 12;

void
init(void) {
    fdt = (uintptr_t) malloc(incbin_device_tree_end - incbin_device_tree_start);
    memcpy((void*)fdt, incbin_device_tree_start, incbin_device_tree_end - incbin_device_tree_start);
    print_info("Initialised\n");
}


void
notified(microkit_channel ch) {
}

microkit_msginfo
protected(microkit_channel ch, microkit_msginfo msginfo) {
    void *addr;
    switch (ch) {
        case 0:
        case 5:
        case 10:
        case 20:
            addr = malloc(microkit_msginfo_get_label(msginfo));
            // print_debug("malloc: addr %p, sz %d\n", addr, microkit_msginfo_get_label(msginfo));
            return seL4_MessageInfo_new((uint64_t) addr,1,0,0);
            break;
        case 1:
        case 6:
        case 11:
        case 21:
            addr = calloc(1, microkit_msginfo_get_label(msginfo));
            // print_debug("calloc: addr %p, sz %d\n", addr, microkit_msginfo_get_label(msginfo));
            return seL4_MessageInfo_new((uint64_t) addr, 1, 0, 0);
            break;
        case 2:
        case 7:
        case 12:
        case 22:
            if ((((uintptr_t) microkit_msginfo_get_label(msginfo)) > __heap_start) && (((uintptr_t) microkit_msginfo_get_label(msginfo)) < __heap_end))
                free((void*)microkit_msginfo_get_label(msginfo));
            return seL4_MessageInfo_new(1, 1, 0, 0);
            break;
        case 4:
            return seL4_MessageInfo_new(fdt, 1, 0, 0);
            break;
        default:
            print_warn("Unexpected channel mem_handler %d\n", ch);
    }
}
