#include "pthread_impl.h"
#include "lock.h"

int __pthread_mutex_unlock(pthread_mutex_t *m)
{
    volatile int* l = (volatile int*)&m->__i;
    UNLOCK(l);
    return 0;
}

weak_alias(__pthread_mutex_unlock, pthread_mutex_unlock);
