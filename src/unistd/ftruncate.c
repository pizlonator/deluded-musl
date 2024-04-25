#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

int ftruncate(int fd, off_t length)
{
    return zsys_ftruncate(fd, length);
}
