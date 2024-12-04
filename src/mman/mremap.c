#define _GNU_SOURCE
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>
#include "syscall.h"

static void dummy(void) { }
weak_alias(dummy, __vm_wait);

void *__mremap(void *old_addr, size_t old_len, size_t new_len, int flags, ...)
{
	va_list list;
	va_start(list, flags);
	void* new_addr;
	if (zcan_va_arg(list))
		new_addr = va_arg(list, void*);
	else
		new_addr = NULL;
	return zsys_mremap(old_addr, old_len, new_len, flags, new_addr);
}

weak_alias(__mremap, mremap);
