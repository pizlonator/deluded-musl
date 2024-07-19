#include <pthread.h>
#include <time.h>
#include <errno.h>
#include "futex.h"
#include "syscall.h"
#include "pthread_impl.h"

int __timedwait_cp(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{
	/* FIXME: This should be a cancel point, but whatever. */
	return zsys_futex_timedwait(addr, val, clk, at, priv);
}

int __timedwait(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{
	return zsys_futex_timedwait(addr, val, clk, at, priv);
}
