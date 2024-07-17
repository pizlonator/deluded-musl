#include <sys/stat.h>
#include <fcntl.h>
#include "syscall.h"

int chmod(const char *path, mode_t mode)
{
    return zsys_chmod(path, mode);
}
