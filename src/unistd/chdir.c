#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

int chdir(const char *path)
{
    return zsys_chdir(path);
}
