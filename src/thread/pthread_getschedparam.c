#include "pthread_impl.h"
#include "lock.h"

int pthread_getschedparam(pthread_t t, int *restrict policy, struct sched_param *restrict param)
{
	int r;
	sigset_t set;
	__block_app_sigs(&set);
	LOCK(t->killlock);
	if (!zthread_get_id(t)) {
		r = ESRCH;
	} else {
                r = -__syscall(SYS_sched_getparam, zthread_get_id(t), param);
		if (!r) {
			*policy = __syscall(SYS_sched_getscheduler, zthread_get_id(t));
		}
	}
	UNLOCK(t->killlock);
	__restore_sigs(&set);
	return r;
}
