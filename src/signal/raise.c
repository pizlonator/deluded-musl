#include <signal.h>
#include <stdint.h>
#include "syscall.h"
#include "pthread_impl.h"
#include <stdfil.h>

int raise(int sig)
{
    return zsys_raise(sig);
}
