#include <stdlib.h>
#include <stdfil.h>

void* aligned_alloc(size_t alignment, size_t size)
{
    return zgc_aligned_alloc(alignment, size);
}
