#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int rmdir(const char *path)
{
    return zsys_rmdir(path);
}
