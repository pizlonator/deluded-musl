#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include "syscall.h"

int ttyname_r(int fd, char *name, size_t size)
{
    return zsys_ttyname_r(fd, name, size);
}
