#define _BSD_SOURCE
#include <string.h>
#include <stdfil.h>

void explicit_bzero(void *d, size_t n)
{
    zmemset(d, 0, n);
}
