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

    switch (zcompare_and_park(addr, val, get_milliseconds(at))) {
    case zpark_condition_failed:
        return 0; /* The real futex wait would return EGAIN, but musl suppresses that to zero. */
    case zpark_timed_out:
        return ETIMEDOUT;
    case zpark_unparked:
        return 0;
    default:
        ZASSERT(!"Bad result from zcompare_and_park");
    }
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
