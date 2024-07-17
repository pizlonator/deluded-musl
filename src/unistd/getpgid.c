#include <unistd.h>
#include "syscall.h"

pid_t getpgid(pid_t pid)
{
    return zsys_getpgid(pid);
}
