#include "pthread_impl.h"

int pthread_rwlock_init(pthread_rwlock_t *restrict rw, const pthread_rwlockattr_t *restrict a)
{
    ZASSERT(!a);
    rw->__i = 0;
    return 0;
}
