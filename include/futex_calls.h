#ifndef _FUTEX_H_
#define _FUTEX_H_

#define __NEED_struct_timespec

#include <bits/alltypes.h>

void futex_wake(volatile int *addr, int cnt, int priv);
void futex_wait(volatile int *addr, int val, int priv);

/* These return the errno as a negative value. */
int futex_timedwait(volatile int *addr, int val, int clock_id, const struct timespec *timeout, int priv);
int futex_unlock_pi(volatile int *addr, int priv);
int futex_lock_pi(volatile int *addr, int priv, const struct timespec *timeout);
int futex_requeue(volatile int *addr, int priv, int wake_count, int requeue_count, volatile int *addr2);

#endif /* _FUTEX_H_ */

