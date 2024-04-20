#include <stdlib.h>
#include <stdfil.h>
#include <errno.h>

void* __libc_calloc(size_t size, size_t count)
{
    if (__builtin_mul_overflow(size, count, &size)) {
        errno = ENOMEM;
        return NULL;
    }

    return zalloc(size); /* zalloc already zeroes memory */
}


