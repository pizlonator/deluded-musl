#include <signal.h>
#include <errno.h>
#include <string.h>
#include "syscall.h"
#include "pthread_impl.h"
#include "libc.h"
#include "lock.h"
#include "ksigaction.h"

static int unmask_done;
static unsigned long handler_set[_NSIG/(8*sizeof(long))];

void __get_handler_set(sigset_t *set)
{
	memcpy(set, handler_set, sizeof handler_set);
}

volatile int __eintr_valid_flag;

int __libc_sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
	if (sa) {
		if ((uintptr_t)sa->sa_handler > 1UL) {
			a_or_l(handler_set+(sig-1)/(8*sizeof(long)),
				1UL<<(sig-1)%(8*sizeof(long)));

			if (!(sa->sa_flags & SA_RESTART)) {
				a_store(&__eintr_valid_flag, 1);
			}
		}
	}
	return zsys_sigaction(sig, sa, old);
}

int __sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
	unsigned long set[_NSIG/(8*sizeof(long))];

	if (sig-32U < 3 || sig-1U >= _NSIG-1) {
		errno = EINVAL;
		return -1;
	}

	/* Doing anything with the disposition of SIGABRT requires a lock,
	 * so that it cannot be changed while abort is terminating the
	 * process and so any change made by abort can't be observed. */
	if (sig == SIGABRT) {
		__block_all_sigs(&set);
		LOCK(__abort_lock);
	}
	int r = __libc_sigaction(sig, sa, old);
	if (sig == SIGABRT) {
		UNLOCK(__abort_lock);
		__restore_sigs(&set);
	}
	return r;
}

weak_alias(__sigaction, sigaction);
