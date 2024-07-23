#define _GNU_SOURCE
#include <poll.h>
#include <signal.h>
#include <errno.h>
#include "syscall.h"

int ppoll(struct pollfd *fds, nfds_t n, const struct timespec *to, const sigset_t *mask)
{
	return zsys_ppoll(fds, n, to, mask);
}
