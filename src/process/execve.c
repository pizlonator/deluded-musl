#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

int execve(const char *path, char *const argv[], char *const envp[])
{
    return zsys_execve(path, argv, envp);
}
