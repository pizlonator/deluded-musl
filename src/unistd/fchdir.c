#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"

int fchdir(int fd)
{
    return zsys_fchdir(fd);
}
