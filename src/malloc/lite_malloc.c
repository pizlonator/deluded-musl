#include <stdlib.h>
#include <stdfil.h>

void *__libc_malloc(size_t n)
{
    return zgc_alloc(n);
}

