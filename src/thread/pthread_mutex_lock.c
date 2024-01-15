#include "pthread_impl.h"
#include <stdfil.h>

int __pthread_mutex_lock(pthread_mutex_t *m)
{
    if (zthread_mutex_lock(m->__p))
        return 0;
    return errno;
}

weak_alias(__pthread_mutex_lock, pthread_mutex_lock);
