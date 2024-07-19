#include "pthread_impl.h"

void futex_wake(volatile int *addr, int cnt, int priv)
{
	__wake(addr, cnt, priv);
}

void futex_wait(volatile int *addr, int val, int priv)
{
	__futexwait(addr, val, priv);
}

int futex_timedwait(volatile int *addr, int val, int clock_id, const struct timespec *timeout, int priv)
{
	return __timedwait(addr, val, clock_id, timeout, priv);
}

int futex_unlock_pi(volatile int *addr, int priv)
{
	if (priv) priv = FUTEX_PRIVATE;
	return __syscall(SYS_futex, addr, FUTEX_UNLOCK_PI|priv);
}

#define IS32BIT(x) !((x)+0x80000000ULL>>32)
#define CLAMP(x) (int)(IS32BIT(x) ? (x) : 0x7fffffffU+((0ULL+(x))>>63))

static int __futex4(volatile void *addr, int op, int val, const struct timespec *to)
{
#ifdef SYS_futex_time64
	time_t s = to ? to->tv_sec : 0;
	long ns = to ? to->tv_nsec : 0;
	int r = -ENOSYS;
	if (SYS_futex == SYS_futex_time64 || !IS32BIT(s))
		r = __syscall(SYS_futex_time64, addr, op, val,
			to ? ((long long[]){s, ns}) : 0);
	if (SYS_futex == SYS_futex_time64 || r!=-ENOSYS) return r;
	to = to ? (void *)(long[]){CLAMP(s), ns} : 0;
#endif
	return __syscall(SYS_futex, addr, op, val, to);
}

int futex_lock_pi(volatile int *addr, int priv, const struct timespec *timeout)
{
	if (priv) priv = FUTEX_PRIVATE;
	return __futex4(addr, FUTEX_LOCK_PI|priv, 0, timeout);
}

void futex_requeue(volatile int *addr, int priv, int wake_count, int requeue_count, volatile int *addr2)
{
	if (priv) priv = FUTEX_PRIVATE;
	__syscall(SYS_futex, addr, FUTEX_REQUEUE|priv, wake_count, requeue_count, addr2) != -ENOSYS
		|| __syscall(SYS_futex, addr, FUTEX_REQUEUE, wake_count, requeue_count, addr2);
}


