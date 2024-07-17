#include <sys/time.h>
#include <errno.h>
#include "syscall.h"
#include <stdfil.h>

int setitimer(int which, const struct itimerval *restrict new, struct itimerval *restrict old)
{
    return zsys_setitimer(which, new, old);
}
