#include "pthread_impl.h"
#include <stdfil.h>

int pthread_mutex_init(pthread_mutex_t *restrict m, const pthread_mutexattr_t *restrict a)
{
    ZASSERT(!a);
    void* zm = zthread_mutex_create();
    if (!zm)
        return errno;
    m->__p = zm;
    return 0;
}
