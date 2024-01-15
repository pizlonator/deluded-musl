#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

uid_t geteuid(void)
{
    return zsys_geteuid();
}
