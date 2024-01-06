#include <stdlib.h>
#include <stdfil.h>

void* aligned_alloc(size_t alignment, size_t size)
{
    return zaligned_alloc(char, alignment, size);
}
