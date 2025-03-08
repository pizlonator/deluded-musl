#include <sys/timerfd.h>
#include <errno.h>
#include "syscall.h"

int timerfd_create(int clockid, int flags)
{
	return zsys_timerfd_create(clockid, flags);
}

int timerfd_settime(int fd, int flags, const struct itimerspec *new, struct itimerspec *old)
{
	return zsys_timerfd_settime(fd, flags, new, old);
}

int timerfd_gettime(int fd, struct itimerspec *cur)
{
	return zsys_timerfd_gettime(fd, cur);
}
