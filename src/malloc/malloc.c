#include <stdlib.h>
#include <stdfil.h>

void* malloc(size_t size)
{
    return zalloc(size);
}
