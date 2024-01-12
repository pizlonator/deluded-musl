#include "pthread_impl.h"
#include <stdfil.h>

int __pthread_rwlock_wrlock(pthread_rwlock_t *rw)
{
    if (zthread_rwlock_wrlock(rw->__p))
        return 0;
    return errno;
}

weak_alias(__pthread_rwlock_wrlock, pthread_rwlock_wrlock);
