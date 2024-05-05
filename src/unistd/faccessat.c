#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "syscall.h"

int faccessat(int fd, const char *filename, int amode, int flag)
{
    return zsys_faccessat(fd, filename, amode, flag);
}
