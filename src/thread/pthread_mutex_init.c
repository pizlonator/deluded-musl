#include "pthread_impl.h"
#include <stdfil.h>

int pthread_mutex_init(pthread_mutex_t *restrict m, const pthread_mutexattr_t *restrict a)
{
    ZASSERT(!a);
    m->__i = 0;
    return 0;
}
