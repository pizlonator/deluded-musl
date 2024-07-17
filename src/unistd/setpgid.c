#include <unistd.h>
#include "syscall.h"

int setpgid(pid_t pid, pid_t pgid)
{
    return zsys_setpgid(pid, pgid);
}
