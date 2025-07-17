#include <signal.h>
#include <errno.h>
#include "syscall.h"

int sigtimedwait(const sigset_t *restrict mask, siginfo_t *restrict si, const struct timespec *restrict timeout)
{
        return zsys_sigtimedwait(mask, si, timeout);
}
