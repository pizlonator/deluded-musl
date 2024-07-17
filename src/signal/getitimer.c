#include <sys/time.h>
#include "syscall.h"
#include <stdfil.h>

int getitimer(int which, struct itimerval *old)
{
    return zsys_getitimer(which, old);
}
