#include <unistd.h>
#include "syscall.h"
#include "libc.h"

int setgid(gid_t gid)
{
    return zsys_setgid(gid);
}
