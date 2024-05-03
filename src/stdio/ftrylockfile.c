#include "stdio_impl.h"
#include "pthread_impl.h"
#include <limits.h>

void __do_orphaned_stdio_locks()
{
}

void __unlist_locked_file(FILE *f)
{
}

void __register_locked_file(FILE *f, pthread_t self)
{
	f->lockcount = 1;
}

int ftrylockfile(FILE *f)
{
	pthread_t self = __pthread_self();
	int tid = zthread_self_id();
	int owner = f->lock;
	if ((owner & ~MAYBE_WAITERS) == tid) {
		if (f->lockcount == LONG_MAX)
			return -1;
		f->lockcount++;
		return 0;
	}
	if (owner < 0) f->lock = owner = 0;
	if (owner || a_cas(&f->lock, 0, tid))
		return -1;
	__register_locked_file(f, self);
	return 0;
}
