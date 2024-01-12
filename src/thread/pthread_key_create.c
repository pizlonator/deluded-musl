#include "pthread_impl.h"
#include "fork_impl.h"
#include <stdfil.h>

void __pthread_key_atfork(int who)
{
    // FIXME
}

int __pthread_key_create(pthread_key_t *k, void (*dtor)(void *))
{
    void* key = zthread_key_create(dtor);
    if (key) {
        *k = key;
        return 0;
    }
    return errno;
}

int __pthread_key_delete(pthread_key_t k)
{
    zthread_key_delete(k);
    return 0;
}

weak_alias(__pthread_key_create, pthread_key_create);
weak_alias(__pthread_key_delete, pthread_key_delete);
