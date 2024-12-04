#define _BSD_SOURCE
#define _GNU_SOURCE
#include <unistd.h>
#include "syscall.h"
#include <sys/time.h>
#include "futex.h"
#include "pthread_impl.h"

#undef syscall

struct futex_args {
	volatile void* uaddr;
	int futex_op;
	unsigned val;
	const struct timespec* timeout;
	volatile void* uaddr2;
	unsigned val3;
};

long syscall(long n, ...)
{
	/* The goal is to have this code support all syscalls, but it doesn't do that, yet. So,
	   it traps on syscalls it doesn't know about.
	
	   That might be OK since the primary use case of syscall(2) is to make syscalls that libc
	   doesn't expose as a function. So, it's unlikely we'll ever see a legitimate call to this
	   function asking for something like SYS_write, for example.
	
	   But if we find such a case, then we'll have to support it because the C programmer is
	   always right! */
	
	void* syscall_args = (char*)zargs() + 8;
	void* callee;
	switch (n) {
	case SYS_futex: {
		struct futex_args* args = (struct futex_args*)syscall_args;
		switch (args->futex_op) {
		case FUTEX_WAIT:
		case FUTEX_WAIT | FUTEX_PRIVATE:
			ZASSERT(!args->timeout);
			zsys_futex_wait(args->uaddr, args->val, args->futex_op & FUTEX_PRIVATE);
			return 0;
		case FUTEX_WAKE:
		case FUTEX_WAKE | FUTEX_PRIVATE:
			zsys_futex_wake(args->uaddr, args->val, args->futex_op & FUTEX_PRIVATE);
			return 0;
		default:
			zerrorf("unsupported futex op: %d (this is a bug in usermusl's syscall "
				"implementation).", args->futex_op);
			return -1;
		}
	}

	case SYS_getdents64:
		callee = zsys_getdents;
		break;

	case SYS_landlock_create_ruleset:
		callee = zsys_landlock_create_ruleset;
		break;

	case SYS_landlock_add_rule:
		callee = zsys_landlock_add_rule;
		break;

	case SYS_landlock_restrict_self:
		callee = zsys_landlock_restrict_self;
		break;

	case SYS_perf_event_open:
		callee = zsys_perf_event_open;
		break;

	case SYS_gettid:
		return __pthread_self()->tid;

	/* FIXME: Implement more syscalls! */

	default:
		zerrorf("unsupported syscall: %ld (this is a bug in usermusl's syscall "
			"implementation).", n);
		return -1;
	}
	
	return *(long*)zcall(callee, syscall_args);
}
