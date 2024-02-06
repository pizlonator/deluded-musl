#include "pthread_impl.h"
#include <stdfil.h>

int __pthread_rwlock_tryrdlock(pthread_rwlock_t *rw)
{
    volatile int *l = (volatile int*)&rw->__i;

    for (;;) {
        unsigned current = *l;

        unsigned read_count = current >> RWLOCK_COUNT_SHIFT;
        unsigned new_read_count = read_count + 1;
        ZASSERT(new_read_count > read_count);
        if ((new_read_count << RWLOCK_COUNT_SHIFT) >> RWLOCK_COUNT_SHIFT != new_read_count)
            return EAGAIN;

        if (current & (RWLOCK_IS_WRITE_HELD_BIT |
                       RWLOCK_IS_WRITE_SPINNING_BIT |
                       RWLOCK_HAS_PARKED_WRITE_BIT))
            return EBUSY;

        unsigned new_value = (current & RWLOCK_BIT_MASK) | (new_read_count << RWLOCK_COUNT_SHIFT);
        if (a_cas(l, current, new_value) == current)
            return 0;
    }
}

weak_alias(__pthread_rwlock_tryrdlock, pthread_rwlock_tryrdlock);
