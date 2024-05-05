#include "pthread_impl.h"
#include "lock.h"

static int trylock_impl(pthread_mutex_t* m)
{
    volatile int* l = (volatile int*)&m->__i;
    if (!TRYLOCK(l))
        return EBUSY;
    return 0;
}

int __pthread_mutex_trylock(pthread_mutex_t *m)
{
    return __mutex_lock_wrapper(m, trylock_impl);
}

weak_alias(__pthread_mutex_trylock, pthread_mutex_trylock);
