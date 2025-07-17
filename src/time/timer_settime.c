#include <time.h>
#include <limits.h>
#include "pthread_impl.h"

#define IS32BIT(x) !((x)+0x80000000ULL>>32)

int timer_settime(timer_t t, int flags, const struct itimerspec *restrict val, struct itimerspec *restrict old)
{
	if ((intptr_t)t < 0) {
		pthread_t td = (void *)((uintptr_t)t << 1);
		t = (void *)(uintptr_t)(td->timer_id & INT_MAX);
	}
	return zsys_timer_settime((intptr_t)t, flags, val, old);
}
