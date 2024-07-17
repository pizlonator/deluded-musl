#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

pid_t getpid(void)
{
    return zsys_getpid();
}
