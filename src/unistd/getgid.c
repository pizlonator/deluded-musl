#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

gid_t getgid(void)
{
    return zsys_getgid();
}
