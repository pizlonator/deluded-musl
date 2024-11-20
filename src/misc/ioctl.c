#include <sys/ioctl.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>
#include "syscall.h"
#include <stdfil.h>

__attribute__((__noinline__)) int ioctl(int fd, int req, ...)
{
	return *(int*)zcall(zsys_ioctl, zargs());
}
