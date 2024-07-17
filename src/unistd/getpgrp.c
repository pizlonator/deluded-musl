#include <unistd.h>
#include "syscall.h"

pid_t getpgrp(void)
{
    return zsys_getpgrp();
}
