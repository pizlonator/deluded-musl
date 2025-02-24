#define _BSD_SOURCE
#define _GNU_SOURCE
#include <unistd.h>
#include "syscall.h"

#undef syscall

long syscall(long n, ...)
{
	return *(long*)zcall(zsys_syscall, zargs());
}
