#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

pid_t setsid(void)
{
    return zsys_setsid();
}
