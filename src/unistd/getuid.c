#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

uid_t getuid(void)
{
    return zsys_getuid();
}
