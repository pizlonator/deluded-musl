#include <stdlib.h>
#include <stdfil.h>

void *__libc_malloc(size_t n)
{
    return zalloc(char, n);
}

