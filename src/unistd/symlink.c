#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int symlink(const char *existing, const char *new)
{
    return zsys_symlink(existing, new);
}
