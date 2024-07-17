#include <dlfcn.h>
#include "dynlink.h"
#include <pizlonated_common_syscalls.h>

void *dlsym(void *restrict p, const char *restrict s)
{
    return zsys_dlsym(p, s);
}
