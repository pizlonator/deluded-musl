#define _BSD_SOURCE
#include <string.h>
#include <stdfil.h>

void explicit_bzero(void *d, size_t n)
{
    memset(d, 0, n); /* This is always explicit in Deluge. */
}
