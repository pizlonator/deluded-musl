#include "pthread_impl.h"
#include "lock.h"

int __pthread_mutex_lock(pthread_mutex_t *m)
{
    volatile int* l = (volatile int*)&m->__i;
    LOCK(l);
    return 0;
}

weak_alias(__pthread_mutex_lock, pthread_mutex_lock);
