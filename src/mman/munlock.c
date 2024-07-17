#include <sys/mman.h>
#include "syscall.h"

int munlock(const void *addr, size_t len)
{
	return zsys_munlock(addr, len);
}
