#include "pthread_impl.h"
#include <stdfil.h>

int pthread_cond_init(pthread_cond_t *restrict c, const pthread_condattr_t *restrict a)
{
    if (a) {
        int pshared;
        ZASSERT(!pthread_condattr_getpshared(a, &pshared));
        if (pshared)
            return ENOSYS;
    }
    c->__i = 0;
    c->__inited = 42;
    return 0;
}
