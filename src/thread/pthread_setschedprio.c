#include "pthread_impl.h"
#include "lock.h"

int pthread_setschedprio(pthread_t t, int prio)
{
	int r;
	sigset_t set;
	__block_app_sigs(&set);
	LOCK(t->killlock);
	r = !zthread_get_id(t) ? ESRCH : -__syscall(SYS_sched_setparam, zthread_get_id(t), &prio);
	UNLOCK(t->killlock);
	__restore_sigs(&set);
	return r;
}
