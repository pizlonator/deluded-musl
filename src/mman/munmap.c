#include <sys/mman.h>
#include "syscall.h"
#include <stdfil.h>

static void dummy(void) { }
weak_alias(dummy, __vm_wait);

int __munmap(void *start, size_t len)
{
	__vm_wait();
        return zsys_munmap(start, len);
}

weak_alias(__munmap, munmap);
