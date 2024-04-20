#include "pthread_impl.h"
#include <threads.h>

static int __pthread_detach(pthread_t t)
{
    /* zthreads don't need no detaching; they just get GC'd, and joining doesn't free them. */
	return 0;
}

weak_alias(__pthread_detach, pthread_detach);
weak_alias(__pthread_detach, thrd_detach);
