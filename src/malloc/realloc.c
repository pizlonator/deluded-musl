#include <stdlib.h>
#include <stdfil.h>

void *realloc(void *p, size_t n)
{
    return zrealloc(p, char, n);
}
