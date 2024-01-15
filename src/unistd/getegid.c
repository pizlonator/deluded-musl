#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

gid_t getegid(void)
{
    return zsys_getegid();
}
