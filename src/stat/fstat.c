#define _BSD_SOURCE
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"
#include <stdfil.h>

int __fstat(int fd, struct stat *st)
{
    return zsys_fstat(fd, st);
}

weak_alias(__fstat, fstat);
