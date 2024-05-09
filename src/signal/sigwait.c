#include <signal.h>
#include <stdfil.h>

int sigwait(const sigset_t *restrict mask, int *restrict sig)
{
    return zsys_sigwait(mask, sig);
}
