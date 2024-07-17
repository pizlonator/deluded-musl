#include <string.h>
#include <stdint.h>

void *memset(void *dest, int c, size_t n)
{
    __builtin_memset(dest, c, n);
    return dest;
}
