#include <time.h>
#include <limits.h>
#include "pthread_impl.h"

int timer_gettime(timer_t t, struct itimerspec *val)
{
	if ((intptr_t)t < 0) {
		pthread_t td = (void *)((uintptr_t)t << 1);
		t = (void *)(uintptr_t)(td->timer_id & INT_MAX);
	}
	return zsys_timer_gettime((intptr_t)t, val);
}
