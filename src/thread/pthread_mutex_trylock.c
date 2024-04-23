#include "pthread_impl.h"
#include "lock.h"

int __pthread_mutex_trylock(pthread_mutex_t *m)
{
    ZASSERT(m->__inited == 42);
    volatile int* l = (volatile int*)&m->__i;
    TRYLOCK(l);
    return 0;
}

weak_alias(__pthread_mutex_trylock, pthread_mutex_trylock);
