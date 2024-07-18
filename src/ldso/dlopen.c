#include <dlfcn.h>
#include "dynlink.h"
#include <pizlonated_syscalls.h>

static void *stub_dlopen(const char *file, int mode)
{
    return zsys_dlopen(file, mode);
}

weak_alias(stub_dlopen, dlopen);
