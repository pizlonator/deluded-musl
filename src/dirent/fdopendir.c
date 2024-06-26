#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "__dirent.h"
#include <pizlonated_musl_syscalls.h>

DIR *fdopendir(int fd)
{
    return zsys_fdopendir(fd);
}
