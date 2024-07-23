#include <sys/epoll.h>
#include <signal.h>
#include <errno.h>
#include "syscall.h"

int epoll_create(int size)
{
	if (size<=0) return __syscall_ret(-EINVAL);
	return epoll_create1(0);
}

int epoll_create1(int flags)
{
	return zsys_epoll_create1(flags);
}

int epoll_ctl(int fd, int op, int fd2, struct epoll_event *ev)
{
	return zsys_epoll_ctl(fd, op, fd2, ev);
}

int epoll_pwait(int fd, struct epoll_event *ev, int cnt, int to, const sigset_t *sigs)
{
	return zsys_epoll_pwait(fd, ev, cnt, to, sigs);
}

int epoll_wait(int fd, struct epoll_event *ev, int cnt, int to)
{
	return zsys_epoll_wait(fd, ev, cnt, to);
}
