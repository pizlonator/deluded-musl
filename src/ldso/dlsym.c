#include <dlfcn.h>
#include "dynlink.h"
#include <stdfil.h>

void *dlsym(void *restrict p, const char *restrict s)
{
    return zsys_dlsym(p, s);
}
