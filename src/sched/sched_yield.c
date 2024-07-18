#include <sched.h>
#include <pizlonated_syscalls.h>

int sched_yield()
{
    zsys_sched_yield();
    return 0;
}
