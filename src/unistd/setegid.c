#include <unistd.h>
#include "libc.h"
#include "syscall.h"

int setegid(gid_t egid)
{
    return zsys_setegid(egid);
}
