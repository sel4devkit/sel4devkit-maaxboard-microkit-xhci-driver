#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* for seeding randomness */
#include <unistd.h>
#include <time.h>

/* for unbuffered input */
#include <fcntl.h>
#include <microkit.h>

char* kbd_buffer;

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
