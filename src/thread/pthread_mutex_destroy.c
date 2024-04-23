#include "pthread_impl.h"
#include <stdfil.h>

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    ZASSERT(mutex->__inited == 42);
    return 0;
}
