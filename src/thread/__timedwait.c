#include <pthread.h>
#include <time.h>
#include <errno.h>
#include "futex.h"
#include "syscall.h"
#include "pthread_impl.h"

int __timedwait_cp(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{
    ZASSERT(priv);
    ZASSERT(clk == CLOCK_REALTIME || !at);

    if (zcompare_and_park(addr, val, get_milliseconds(at)))
        return 0;
    return ETIMEDOUT;
}

int __timedwait(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{
	int cs, r;
	//__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	r = __timedwait_cp(addr, val, clk, at, priv);
	//__pthread_setcancelstate(cs, 0);
	return r;
}
