#include "pthread_impl.h"
#include <stdfil.h>

typedef struct {
    pthread_cond_t* c;
    pthread_mutex_t* m;
} wait_data;

_Bool condition_callback(void* arg)
{
    wait_data* data = (wait_data*)arg;
    data->c->__i = 1;
    return 1;
}

void before_sleep_callback(void* arg)
{
    wait_data* data = (wait_data*)arg;
    ZASSERT(!pthread_mutex_unlock(data->m));
}

int __pthread_cond_timedwait(pthread_cond_t *restrict c, pthread_mutex_t *restrict m, const struct timespec *restrict ts)
{
    wait_data data;
    data.c = c;
    data.m = m;
    _Bool result = zpark_if(
        &c->__i, condition_callback, before_sleep_callback, &data, get_milliseconds(ts));
    pthread_mutex_lock(m);
    return result ? 0 : ETIMEDOUT;
}

weak_alias(__pthread_cond_timedwait, pthread_cond_timedwait);
