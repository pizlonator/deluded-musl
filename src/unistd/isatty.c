#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "syscall.h"
#include <stdfil.h>

int isatty(int fd)
{
    return zsys_isatty(fd);
}
