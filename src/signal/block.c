#include "pthread_impl.h"
#include "syscall.h"
#include <signal.h>

void __block_all_sigs(void *set)
{
    sigset_t all_mask;
    sigfillset(&all_mask);
    zsys_sigprocmask(SIG_BLOCK, &all_mask, set);
}

void __block_app_sigs(void *set)
{
    sigset_t all_mask;
    /* FIXME: Is this right? */
    sigfillset(&all_mask);
    zsys_sigprocmask(SIG_BLOCK, &all_mask, set);
}

void __restore_sigs(void *set)
{
    zsys_sigprocmask(SIG_SETMASK, set, 0);
}
