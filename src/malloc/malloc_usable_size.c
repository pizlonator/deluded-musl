#include <stdlib.h>
#include <stdfil.h>

size_t malloc_usable_size(void *p)
{
    if (!zhasvalidcap(p) || !zinbounds(p))
        return 0;
    return (char*)zgetupper(p) - (char*)p;
}
