#include "pthread_impl.h"
#include <stdfil.h>

int pthread_rwlock_init(pthread_rwlock_t *restrict rw, const pthread_rwlockattr_t *restrict a)
{
    ZASSERT(!a);
    void* zrw = zthread_rwlock_create();
    if (!zrw)
        return errno;
    rw->__p = zrw;
    return 0;
}
