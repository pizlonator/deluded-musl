#include "pthread_impl.h"
#include <stdfil.h>

int __pthread_rwlock_rdlock(pthread_rwlock_t *rw)
{
    volatile int *l = (volatile int*)&rw->__i;

    unsigned spin_count = 0;
    for (;;) {
        unsigned current = *l;

        unsigned read_count = current >> RWLOCK_COUNT_SHIFT;
        unsigned new_read_count = read_count + 1;
        ZASSERT(new_read_count > read_count);
        if ((new_read_count << RWLOCK_COUNT_SHIFT) >> RWLOCK_COUNT_SHIFT != new_read_count)
            return EAGAIN;

        if (!(current & (RWLOCK_IS_WRITE_HELD_BIT |
                         RWLOCK_IS_WRITE_SPINNING_BIT |
                         RWLOCK_HAS_PARKED_WRITE_BIT))) {
            unsigned new_value = (current & RWLOCK_BIT_MASK) | (new_read_count << RWLOCK_COUNT_SHIFT);
            if (a_cas(l, current, new_value) == current)
                return 0;
            continue;
        }

        /* Fun fact: readers will spin, instead of parking, if a writer is spinning but hasn't parked
           yet. */
        if (!(current & (RWLOCK_HAS_PARKED_READ_BIT | RWLOCK_HAS_PARKED_WRITE_BIT))
            && spin_count < SPIN_LIMIT) {
            spin_count++;
            zsys_sched_yield();
        }

        if (!(current & RWLOCK_HAS_PARKED_READ_BIT)) {
            if (a_cas(l, current, current | RWLOCK_HAS_PARKED_READ_BIT) != current)
                continue;
            current |= RWLOCK_HAS_PARKED_READ_BIT;
        }

        ZASSERT(current & RWLOCK_HAS_PARKED_READ_BIT);
        ZASSERT(current & (RWLOCK_IS_WRITE_HELD_BIT |
                           RWLOCK_IS_WRITE_SPINNING_BIT |
                           RWLOCK_HAS_PARKED_WRITE_BIT));

        zcompare_and_park(RWLOCK_READ_PARK_ADDR(l), current, 1. / 0.);
    }
}

weak_alias(__pthread_rwlock_rdlock, pthread_rwlock_rdlock);
