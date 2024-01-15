#include "pthread_impl.h"
#include <stdfil.h>

int __pthread_mutex_timedlock(pthread_mutex_t *restrict m, const struct timespec *restrict at)
{
    zerror("pthreadz_mutex_timedlock not implemented");
    return 0;
}

weak_alias(__pthread_mutex_timedlock, pthread_mutex_timedlock);
