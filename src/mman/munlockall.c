#include <sys/mman.h>
#include "syscall.h"

int munlockall(void)
{
	return zsys_munlockall();
}
