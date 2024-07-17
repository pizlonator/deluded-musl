#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

off_t __lseek(int fd, off_t offset, int whence)
{
    return zsys_lseek(fd, offset, whence);
}

weak_alias(__lseek, lseek);
