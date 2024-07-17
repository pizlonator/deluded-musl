#include <sys/resource.h>
#include <errno.h>
#include "syscall.h"
#include <stdfil.h>

int getrlimit(int resource, struct rlimit *rlim)
{
    return zsys_getrlimit(resource, rlim);
}
