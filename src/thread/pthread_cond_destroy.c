#include "pthread_impl.h"

int pthread_cond_destroy(pthread_cond_t *c)
{
    ZASSERT(c->__inited == 42);
    return 0;
}
