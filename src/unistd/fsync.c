#include <unistd.h>
#include "syscall.h"

int fsync(int fd)
{
    return zsys_fsync(fd);
}
