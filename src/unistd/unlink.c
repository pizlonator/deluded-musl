#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int unlink(const char *path)
{
    return zsys_unlink(path);
}
