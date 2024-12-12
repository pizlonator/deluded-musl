#include <time.h>
#include <errno.h>
#include "syscall.h"

int __clock_nanosleep(clockid_t clk, int flags, const struct timespec *req, struct timespec *rem)
{
	return zsys_clock_nanosleep(clk, flags, req, rem);
}

weak_alias(__clock_nanosleep, clock_nanosleep);
