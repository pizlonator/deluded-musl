#include "pthread_impl.h"
#include "lock.h"

int pthread_setschedparam(pthread_t t, int policy, const struct sched_param *param)
{
	int r;
	sigset_t set;
	__block_app_sigs(&set);
	LOCK(t->killlock);
	r = !zthread_get_id(t) ? ESRCH : -__syscall(SYS_sched_setscheduler, zthread_get_id(t), policy, param);
	UNLOCK(t->killlock);
	__restore_sigs(&set);
	return r;
}