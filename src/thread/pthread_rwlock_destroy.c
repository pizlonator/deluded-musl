#include "pthread_impl.h"
#include <stdfil.h>

int pthread_rwlock_destroy(pthread_rwlock_t *rw)
{
    zthread_rwlock_delete(rw->__p);
    return 0;
}
