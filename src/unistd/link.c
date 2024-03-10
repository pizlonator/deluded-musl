#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int link(const char *existing, const char *new)
{
    return zsys_link(existing, new);
}
