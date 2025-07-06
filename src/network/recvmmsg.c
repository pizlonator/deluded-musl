#define _GNU_SOURCE
#include <sys/socket.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "syscall.h"

int recvmmsg(int fd, struct mmsghdr *msgvec, unsigned int vlen, unsigned int flags, struct timespec *timeout)
{
	return zsys_recvmmsg(fd, msgvec, vlen, flags, timeout);
}
