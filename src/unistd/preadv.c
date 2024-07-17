#define _BSD_SOURCE
#include <sys/uio.h>
#include <unistd.h>
#include "syscall.h"

ssize_t preadv(int fd, const struct iovec *iov, int count, off_t ofs)
{
	return zsys_preadv(fd, iov, count, ofs);
}
