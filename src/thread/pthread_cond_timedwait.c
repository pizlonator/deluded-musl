#include "pthread_impl.h"

/*
 * struct waiter
 *
 * Waiter objects have automatic storage on the waiting thread, and
 * are used in building a linked list representing waiters currently
 * waiting on the condition variable or a group of waiters woken
 * together by a broadcast or signal; in the case of signal, this is a
 * degenerate list of one member.
 *
 * Waiter lists attached to the condition variable itself are
 * protected by the lock on the cv. Detached waiter lists are never
 * modified again, but can only be traversed in reverse order, and are
 * protected by the "barrier" locks in each node, which are unlocked
 * in turn to control wake order.
 *
 * Since process-shared cond var semantics do not necessarily allow
 * one thread to see another's automatic storage (they may be in
 * different processes), the waiter list is not used for the
 * process-shared case, but the structure is still used to store data
 * needed by the cancellation cleanup handler.
 */

struct waiter {
	struct waiter *prev, *next;
	volatile int state, barrier;
	volatile int *notify;
};

/* Self-synchronized-destruction-safe lock functions */

static inline void lock(volatile int *l)
{
	if (a_cas(l, 0, 1)) {
		a_cas(l, 1, 2);
		do __wait(l, 0, 2, 1);
		while (a_cas(l, 0, 2));
	}
}

static inline void unlock(volatile int *l)
{
	if (a_swap(l, 0)==2)
		__wake(l, 1, 1);
}

static inline void unlock_requeue(volatile int *l, volatile int *r, int w)
{
	a_store(l, 0);
	if (w) __wake(l, 1, 1);
	else __syscall(SYS_futex, l, FUTEX_REQUEUE|FUTEX_PRIVATE, 0, 1, r) != -ENOSYS
		|| __syscall(SYS_futex, l, FUTEX_REQUEUE, 0, 1, r);
}

enum {
	WAITING,
	SIGNALED,
	LEAVING,
};

int __pthread_cond_timedwait(pthread_cond_t *restrict c, pthread_mutex_t *restrict m, const struct timespec *restrict ts)
{
    zerror("pthread_cond_timedwait not implemented");
}

int __private_cond_signal(pthread_cond_t *c, int n)
{
	struct waiter *p, *first=0;
	volatile int ref = 0;
	int cur;

	lock(&c->_c_lock);
	for (p=c->_c_tail; n && p; p=p->prev) {
		if (a_cas(&p->state, WAITING, SIGNALED) != WAITING) {
			ref++;
			p->notify = &ref;
		} else {
			n--;
			if (!first) first=p;
		}
	}
	/* Split the list, leaving any remainder on the cv. */
	if (p) {
		if (p->next) p->next->prev = 0;
		p->next = 0;
	} else {
		c->_c_head = 0;
	}
	c->_c_tail = p;
	unlock(&c->_c_lock);

	/* Wait for any waiters in the LEAVING state to remove
	 * themselves from the list before returning or allowing
	 * signaled threads to proceed. */
	while ((cur = ref)) __wait(&ref, 0, cur, 1);

	/* Allow first signaled waiter, if any, to proceed. */
	if (first) unlock(&first->barrier);

	return 0;
}

weak_alias(__pthread_cond_timedwait, pthread_cond_timedwait);
