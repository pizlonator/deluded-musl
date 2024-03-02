#include <unistd.h>
#include "syscall.h"
#include "libc.h"

int setregid(gid_t rgid, gid_t egid)
{
    return zsys_setregid(rgid, egid);
}
