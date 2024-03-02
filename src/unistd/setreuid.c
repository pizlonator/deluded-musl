#include <unistd.h>
#include "syscall.h"
#include "libc.h"

int setreuid(uid_t ruid, uid_t euid)
{
    return zsys_setreuid(ruid, euid);
}
