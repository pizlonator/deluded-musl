#include "pthread_impl.h"
#include <stdfil.h>

int pthread_setspecific(pthread_key_t k, const void *x)
{
    if (zthread_setspecific(k, x))
        return 0;
    return errno;
}
