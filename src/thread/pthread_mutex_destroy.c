#include "pthread_impl.h"
#include <stdfil.h>

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    zthread_mutex_delete(mutex->__p);
    return 0;
}
