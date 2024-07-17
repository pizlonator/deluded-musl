#include <unistd.h>
#include "syscall.h"

ssize_t pread(int fd, void *buf, size_t size, off_t ofs)
{
	return zsys_pread(fd, buf, size, ofs);
}
