#include "pthread_impl.h"
#include "lock.h"

static int lock_impl(pthread_mutex_t* m)
{
    volatile int* l = (volatile int*)&m->__i;
    LOCK(l);
    return 0;
}

int __pthread_mutex_lock(pthread_mutex_t *m)
{
    return __mutex_lock_wrapper(m, lock_impl);
}

weak_alias(__pthread_mutex_lock, pthread_mutex_lock);
