#include <sys/mman.h>
#include "syscall.h"

int mlock(const void *addr, size_t len)
{
	return zsys_mlock(addr, len);
}
