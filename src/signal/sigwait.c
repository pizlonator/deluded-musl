#include <signal.h>
#include <pizlonated_musl_syscalls.h>

int sigwait(const sigset_t *restrict mask, int *restrict sig)
{
    return zsys_sigwait(mask, sig);
}
