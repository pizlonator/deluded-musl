#include "pthread_impl.h"
#include <threads.h>
#include <stdfil.h>

static void *__pthread_getspecific(pthread_key_t k)
{
    return zthread_getspecific(k);
}

weak_alias(__pthread_getspecific, pthread_getspecific);
weak_alias(__pthread_getspecific, tss_get);
