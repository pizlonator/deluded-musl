#include <dlfcn.h>
#include "dynlink.h"
#include <stdfil.h>

static void *stub_dlopen(const char *file, int mode)
{
    return zsys_dlopen(file, mode);
}

weak_alias(stub_dlopen, dlopen);
