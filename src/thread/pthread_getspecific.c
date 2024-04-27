#include "pthread_impl.h"
#include <threads.h>
#include <stdfil.h>

static void *__pthread_getspecific(pthread_key_t k)
{
    internal_thread_data* data = get_internal_thread_data();
    thread_local_data* local = data->thread_locals + k;
    if (zinbounds(local) && local->version == thread_locals[k].version)
        return local->value;
    return NULL;
}

weak_alias(__pthread_getspecific, pthread_getspecific);
weak_alias(__pthread_getspecific, tss_get);

/* This is a total hack to make FilPizlonator.cpp simpler for now. This should die
   eventually. */
void* pthread_getspecific_with_default_np(pthread_key_t k, void* (*default_initializer)(void))
{
    void* result = pthread_getspecific(k);
    if (!result) {
        result = default_initializer();
        pthread_setspecific(k, result);
    }
    return result;
}
