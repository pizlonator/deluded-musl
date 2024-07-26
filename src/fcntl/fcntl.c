#define _GNU_SOURCE
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include "syscall.h"

int fcntl(int fd, int cmd, ...)
{
	return (int)zcall_int(zsys_fcntl, zargs());
}
