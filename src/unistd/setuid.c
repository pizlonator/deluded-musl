#include <unistd.h>
#include "syscall.h"
#include "libc.h"
#include <stdfil.h>

int setuid(uid_t uid)
{
    return zsys_setuid(uid);
}
