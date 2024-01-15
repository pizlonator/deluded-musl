#include <signal.h>
#include "syscall.h"
#include <stdfil.h>

void (*signal(int sig, void (*func)(int)))(int)
{
    return zsys_signal(sig, func);
}

weak_alias(signal, bsd_signal);
weak_alias(signal, __sysv_signal);
