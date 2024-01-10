#include <stdlib.h>
#include "syscall.h"
#include <stdfil.h>

_Noreturn void _Exit(int ec)
{
    //__syscall(SYS_exit_group, ec);
    for (;;) zsys_exit(ec);
}
