#include <stdlib.h>
#include <stdfil.h>

void *realloc(void *p, size_t n)
{
    return zgc_realloc(p, n);
}
