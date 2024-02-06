#include <sched.h>
#include <stdfil.h>

int sched_yield()
{
    zsys_sched_yield();
    return 0;
}
