#include <sys/wait.h>
#include "syscall.h"
#include <stdfil.h>

pid_t waitpid(pid_t pid, int *status, int options)
{
    return zsys_waitpid(pid, status, options);
}
