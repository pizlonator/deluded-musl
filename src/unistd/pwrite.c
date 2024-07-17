#include <unistd.h>
#include "syscall.h"

ssize_t pwrite(int fd, const void *buf, size_t size, off_t ofs)
{
	return zsys_pwrite(fd, buf, size, ofs);
}
