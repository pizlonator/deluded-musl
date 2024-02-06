#include "pthread_impl.h"
#include <stdfil.h>

int __pthread_rwlock_trywrlock(pthread_rwlock_t *rw)
{
    volatile int *l = (volatile int*)&rw->__i;

    for (;;) {
        unsigned current = *l;

        if (current & RWLOCK_IS_WRITE_HELD_BIT)
            return EBUSY;
        if (current >> RWLOCK_COUNT_SHIFT)
            return EBUSY;

        if (a_cas(l, current, (current | RWLOCK_IS_WRITE_HELD_BIT) & ~RWLOCK_IS_WRITE_SPINNING_BIT)
            == current)
            return 0;
    }
}

weak_alias(__pthread_rwlock_trywrlock, pthread_rwlock_trywrlock);
