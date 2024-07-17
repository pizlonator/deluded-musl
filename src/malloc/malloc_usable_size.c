#include <stdlib.h>
#include <stdfil.h>

size_t malloc_usable_size(void *p)
{
    return (char*)zgetupper(p) - (char*)p;
}
