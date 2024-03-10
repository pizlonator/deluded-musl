#include <stdio.h>
#include <fcntl.h>
#include "syscall.h"

int rename(const char *old, const char *new)
{
    return zsys_rename(old, new);
}
