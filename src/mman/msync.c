#include <sys/mman.h>
#include "syscall.h"

int msync(void *start, size_t len, int flags)
{
	return zsys_msync(start, len, flags);
}
