#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

pid_t getppid(void)
{
    return zsys_getppid();
}
