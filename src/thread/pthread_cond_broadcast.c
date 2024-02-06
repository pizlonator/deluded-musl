#include "pthread_impl.h"

int pthread_cond_broadcast(pthread_cond_t *c)
{
    if (!c->__i)
        return 0;
    c->__i = 0;
    zunpark(&c->__i, -1);
    return 0;
}
