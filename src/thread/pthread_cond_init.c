#include "pthread_impl.h"
#include <stdfil.h>

int pthread_cond_init(pthread_cond_t *restrict c, const pthread_condattr_t *restrict a)
{
    ZASSERT(!a);
    c->__i = 0;
    return 0;
}
