#include <string.h>
#include <stdint.h>
#include <endian.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    __builtin_memcpy(dest, src, n);
    return dest;
}
