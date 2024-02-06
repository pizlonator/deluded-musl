#include "pthread_impl.h"
#include <stdfil.h>

int __pthread_rwlock_wrlock(pthread_rwlock_t *rw)
{
    volatile int* l = (volatile int*)&rw->__i;
    if (a_cas(l, 0, RWLOCK_IS_WRITE_HELD_BIT) == 0)
        return 0;

    unsigned spin_count = 0;
    for (;;) {
        unsigned current = *l;

        if (!(current & RWLOCK_IS_WRITE_HELD_BIT)
            && !(current >> RWLOCK_COUNT_SHIFT)) {
            if (a_cas(l, current, (current | RWLOCK_IS_WRITE_HELD_BIT) & ~RWLOCK_IS_WRITE_SPINNING_BIT)
                == current)
                return 0;
            continue;
        }

        if (!(current & RWLOCK_HAS_PARKED_WRITE_BIT) && spin_count < SPIN_LIMIT) {
            if (!(current & RWLOCK_IS_WRITE_SPINNING_BIT)) {
                if (a_cas(l, current, current | RWLOCK_IS_WRITE_SPINNING_BIT) != current)
                    continue;
            }

            spin_count++;
            zsys_sched_yield();
        }

        if (!(current & RWLOCK_HAS_PARKED_WRITE_BIT)) {
            if (a_cas(l, current, current | RWLOCK_HAS_PARKED_WRITE_BIT) != current)
                continue;
            current |= RWLOCK_HAS_PARKED_WRITE_BIT;
        }

        ZASSERT(current & RWLOCK_HAS_PARKED_WRITE_BIT);
        ZASSERT((current & RWLOCK_IS_WRITE_HELD_BIT) || (current >> RWLOCK_COUNT_SHIFT));

        zcompare_and_park(RWLOCK_WRITE_PARK_ADDR(l), current, 1. / 0.);
    }

    ZASSERT(!"Should not be reached");
    return 0;
}

weak_alias(__pthread_rwlock_wrlock, pthread_rwlock_wrlock);
