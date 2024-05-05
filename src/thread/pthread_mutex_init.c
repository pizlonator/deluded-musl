#include "pthread_impl.h"
#include <stdfil.h>

int pthread_mutex_init(pthread_mutex_t *restrict m, const pthread_mutexattr_t *restrict a)
{
    m->__tid = 0;
    m->__recurse_count = UINT_MAX;
    if (a) {
        int type;
        pthread_mutexattr_gettype(a, &type);
        ZASSERT(type == PTHREAD_MUTEX_NORMAL || type == PTHREAD_MUTEX_RECURSIVE);
        if (type == PTHREAD_MUTEX_RECURSIVE)
            m->__recurse_count = 0;
        int pshared;
        pthread_mutexattr_getpshared(a, &pshared);
        ZASSERT(!pshared);
        int robust;
        pthread_mutexattr_getrobust(a, &robust);
        ZASSERT(robust == PTHREAD_MUTEX_STALLED);
    }
    m->__i = 0;
    return 0;
}
