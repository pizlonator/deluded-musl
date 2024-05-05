#include "pthread_impl.h"
#include "lock.h"

int __pthread_mutex_unlock(pthread_mutex_t *m)
{
    volatile int* l = (volatile int*)&m->__i;
    if (m->__recurse_count != UINT_MAX) {
        if (m->__tid != zthread_self_id())
            return EPERM;
        ZASSERT(m->__recurse_count);
        if (!--m->__recurse_count)
            m->__tid = 0;
        else
            return 0;
    }
    UNLOCK(l);
    return 0;
}

weak_alias(__pthread_mutex_unlock, pthread_mutex_unlock);
