#include "pthread_impl.h"
#include <stdfil.h>

int pthread_setspecific(pthread_key_t k, const void *x)
{
    internal_thread_data* data = get_internal_thread_data();
    if ((size_t)k >= zlength(data->thread_locals)) {
        size_t new_length = zlength(thread_locals);
        if ((size_t)k >= new_length)
            return EINVAL;
        thread_local_data* new_locals = zalloc(thread_local_data, new_length);
        if (!new_locals)
            return ENOMEM;
        __builtin_memcpy(new_locals, data->thread_locals, zlength(data->thread_locals) * sizeof(thread_local_data));
        zfree(data->thread_locals);
        data->thread_locals = new_locals;
        ZASSERT(zlength(data->thread_locals) == new_length);
    }
    ZASSERT((size_t)k < zlength(data->thread_locals));
    if (!thread_locals[k].is_active)
        return EINVAL;
    thread_local_data* local = data->thread_locals + k;
    local->value = x;
    local->version = thread_locals[k].version;
    return 0;
}
