#include <stdlib.h>
#include "syscall.h"
#include <stdfil.h>

_Noreturn void _Exit(int ec)
{
	zsys_exit_hard(ec);
}
