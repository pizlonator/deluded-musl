#include <unistd.h>
#include "syscall.h"
#include "libc.h"

int seteuid(uid_t euid)
{
    return zsys_seteuid(euid);
}
