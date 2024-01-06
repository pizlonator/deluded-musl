#include <stdlib.h>
#include <stdfil.h>

void free(void *p)
{
    zfree(p);
}

void __libc_free(void *p)
{
    zfree(p);
}
