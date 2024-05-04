#include <dlfcn.h>
#include "dynlink.h"

int dlclose(void *p)
{
    /* FIXME: We could, and should, implement dlclosing eventually. */
    return 0;
}
