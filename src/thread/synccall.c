#include "pthread_impl.h"
#include <semaphore.h>
#include <string.h>

static void dummy_0(void)
{
}

weak_alias(dummy_0, __tl_lock);
weak_alias(dummy_0, __tl_unlock);

static int target_tid;
static void (*callback)(void *), *context;
static sem_t target_sem, caller_sem, exit_sem;

static void dummy(void *p)
{
}

static void handler(int sig)
{
	if (zthread_self_id() != target_tid) return;

	int old_errno = errno;

	/* Inform caller we have received signal and wait for
	 * the caller to let us make the callback. */
	sem_post(&caller_sem);
	sem_wait(&target_sem);

	callback(context);

	/* Inform caller we've complered the callback and wait
	 * for the caller to release us to return. */
	sem_post(&caller_sem);
	sem_wait(&exit_sem);

	/* Inform caller we are returning and state is destroyable. */
	sem_post(&caller_sem);

	errno = old_errno;
}

