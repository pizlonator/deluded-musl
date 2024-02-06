#include "pthread_impl.h"

static void callback(_Bool did_unpark_thread, _Bool may_have_more_threads, void* arg)
{
    pthread_cond_t* c = (pthread_cond_t*)arg;
    if (!may_have_more_threads)
        c->__i = 0;
}

int pthread_cond_signal(pthread_cond_t *c)
{
    if (!c->__i)
        return 0;
    zunpark_one(&c->__i, callback, c);
}
