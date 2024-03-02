#include <unistd.h>
#include <errno.h>
#include "libc.h"
#include "lock.h"
#include "pthread_impl.h"
#include "fork_impl.h"
#include <stdfil.h>

static volatile int *const dummy_lockptr = 0;

weak_alias(dummy_lockptr, __at_quick_exit_lockptr);
weak_alias(dummy_lockptr, __atexit_lockptr);
weak_alias(dummy_lockptr, __gettext_lockptr);
weak_alias(dummy_lockptr, __locale_lockptr);
weak_alias(dummy_lockptr, __random_lockptr);
weak_alias(dummy_lockptr, __sem_open_lockptr);
weak_alias(dummy_lockptr, __stdio_ofl_lockptr);
weak_alias(dummy_lockptr, __syslog_lockptr);
weak_alias(dummy_lockptr, __timezone_lockptr);
weak_alias(dummy_lockptr, __bump_lockptr);

weak_alias(dummy_lockptr, __vmlock_lockptr);

static volatile int *const *const atfork_locks[] = {
	&__at_quick_exit_lockptr,
	&__atexit_lockptr,
	&__gettext_lockptr,
	&__locale_lockptr,
	&__random_lockptr,
	&__sem_open_lockptr,
	&__stdio_ofl_lockptr,
	&__syslog_lockptr,
	&__timezone_lockptr,
	&__bump_lockptr,
};

static void dummy(int x) { }
weak_alias(dummy, __fork_handler);
weak_alias(dummy, __malloc_atfork);
weak_alias(dummy, __aio_atfork);
weak_alias(dummy, __pthread_key_atfork);
weak_alias(dummy, __ldso_atfork);

static void dummy_0(void) { }
weak_alias(dummy_0, __tl_lock);
weak_alias(dummy_0, __tl_unlock);

pid_t fork(void)
{
    /* This works without dealing with any locks or whatever because currently, zsys_fork() will
       kill the shit out of the process if there were ever any threads created. */
    return zsys_fork();
}
