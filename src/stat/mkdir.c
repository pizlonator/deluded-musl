#include <sys/stat.h>
#include <fcntl.h>
#include "syscall.h"
#include <stdfil.h>

int mkdir(const char *path, mode_t mode)
{
    return zsys_mkdirat(AT_FDCWD, path, mode);
}
