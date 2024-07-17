#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

int pipe(int fd[2])
{
    return zsys_pipe(fd);
}
