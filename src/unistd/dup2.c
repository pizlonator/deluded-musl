#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"
#include <stdfil.h>

int dup2(int old, int new)
{
    return zsys_dup2(old, new);
}
