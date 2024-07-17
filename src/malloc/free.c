#include <stdlib.h>
#include <stdfil.h>

void free(void *p)
{
    zgc_free(p);
}

void __libc_free(void *p)
{
    zgc_free(p);
}
