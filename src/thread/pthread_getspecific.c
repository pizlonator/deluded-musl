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
