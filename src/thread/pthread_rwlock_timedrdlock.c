#include "pthread_impl.h"
#include <stdfil.h>

int __pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rw, const struct timespec *restrict at)
{
    zerror("__pthread_rwlock_timedrdlock not implemented");
    return 0;
}

weak_alias(__pthread_rwlock_timedrdlock, pthread_rwlock_timedrdlock);
