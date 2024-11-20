#define _GNU_SOURCE
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include "syscall.h"

__attribute__((__noinline__)) int fcntl(int fd, int cmd, ...)
{
	return *(int*)zcall(zsys_fcntl, zargs());
}
