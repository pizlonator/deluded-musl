#include <signal.h>
#include <errno.h>
#include "syscall.h"
#include <stdfil.h>

int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict old)
{
    int result = zsys_sigprocmask(how, set, old);
    if (result < 0)
        return errno;
    return 0;
}
