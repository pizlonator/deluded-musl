#define _GNU_SOURCE
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"

int accept4(int fd, struct sockaddr *restrict addr, socklen_t *restrict len, int flg)
{
	return zsys_accept4(fd, addr, len, flg);
}
