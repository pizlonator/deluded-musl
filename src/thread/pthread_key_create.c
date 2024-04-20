#include "pthread_impl.h"
#include "fork_impl.h"
#include "lock.h"
#include <stdfil.h>

volatile int thread_local_lock;
thread_local_descriptor* thread_locals;
size_t next_free_descriptor = __SIZE_MAX__;

void __pthread_key_atfork(int who)
{
    zerror("pthread_key_atfork not implemented");
}

int __pthread_key_create(pthread_key_t *k, void (*dtor)(void *))
{
    LOCK(&thread_local_lock);
    
    if (next_free_descriptor == __SIZE_MAX__) {
        size_t new_size;
        if (!thread_locals)
            new_size = 10;
        else
            new_size = zlength(thread_locals) * 2;

        thread_local_descriptor* new_thread_locals = zalloc(sizeof(thread_local_descriptor) * new_size);
        ZASSERT(zlength(new_thread_locals) == new_size);
        __builtin_memcpy(new_thread_locals, thread_locals, zlength(thread_locals) * sizeof(thread_local_descriptor));

        size_t index;
        for (index = zlength(thread_locals); index < new_size; ++index) {
            thread_local_descriptor* descriptor = new_thread_locals + index;
            descriptor->destructor = NULL;
            descriptor->is_active = 0;
            descriptor->version = 1;
            if (index == new_size - 1)
                descriptor->next_free_index = __SIZE_MAX__;
            else
                descriptor->next_free_index = index + 1;
        }

        next_free_descriptor = zlength(thread_locals);

        zstore_store_fence();

        thread_locals = new_thread_locals;

        /* leak the old thread_locals so there's no race with getspecific or thread death. */
    }

    ZASSERT(next_free_descriptor != __SIZE_MAX__);
    ZASSERT(next_free_descriptor < zlength(thread_locals));

    thread_local_descriptor* result = thread_locals + next_free_descriptor;
    next_free_descriptor = result->next_free_index;

    result->destructor = dtor;
    result->is_active = 1;
    result->next_free_index = 0;

    *k = (int)(result - thread_locals);

    UNLOCK(&thread_local_lock);
    
    return 0;
}

int __pthread_key_delete(pthread_key_t k)
{
    LOCK(&thread_local_lock);

    thread_local_descriptor* descriptor = thread_locals + k;
    descriptor->version++;
    descriptor->destructor = NULL;
    descriptor->is_active = 0;
    descriptor->next_free_index = next_free_descriptor;
    next_free_descriptor = k;

    UNLOCK(&thread_local_lock);
    
    return 0;
}

weak_alias(__pthread_key_create, pthread_key_create);
weak_alias(__pthread_key_delete, pthread_key_delete);
