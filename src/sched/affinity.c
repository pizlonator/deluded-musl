#define _GNU_SOURCE
#include <sched.h>
#include <string.h>
#include "pthread_impl.h"
#include "syscall.h"
#include <stdfil.h>

int sched_setaffinity(pid_t tid, size_t size, const cpu_set_t *set)
{
    errno = ENOSYS;
    return -1;
}

int pthread_setaffinity_np(pthread_t td, size_t size, const cpu_set_t *set)
{
    return ENOSYS;
}

static int do_getaffinity(size_t size, cpu_set_t *set)
{
    int numcores = zsys_numcores();
    if (numcores < 0)
        return -1;
    cpu_set_t my_set;
    memset(&my_set, 0, sizeof(my_set));
    int index;
    for (index = numcores; index--;)
        CPU_SET(index, &my_set);
    memcpy(set, &my_set, size);
    return 0;
}

int sched_getaffinity(pid_t tid, size_t size, cpu_set_t *set)
{
    return do_getaffinity(size, set);
}

int pthread_getaffinity_np(pthread_t td, size_t size, cpu_set_t *set)
{
    if (do_getaffinity(size, set) < 0)
        return errno;
    return 0;
}
