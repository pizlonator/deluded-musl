#include "pthread_impl.h"
#include <stdfil.h>

static void unlock_write_for_write_callback(_Bool did_unpark_thread, _Bool may_have_more_threads, void* arg)
{
    volatile int* l = (volatile int*)arg;

    for (;;) {
        unsigned current = *l;
        
        ZASSERT(current & RWLOCK_IS_WRITE_HELD_BIT);
        ZASSERT(current & RWLOCK_HAS_PARKED_WRITE_BIT);
        
        unsigned new_value = current & ~RWLOCK_IS_WRITE_HELD_BIT;
        
        if (!may_have_more_threads)
            new_value &= ~RWLOCK_HAS_PARKED_WRITE_BIT;

        if (a_cas(l, current, new_value) == current)
            return;
    }
}

static void unlock_write(volatile int *l)
{
    for (;;) {
        unsigned current = *l;

        ZASSERT(current & RWLOCK_IS_WRITE_HELD_BIT);
        ZASSERT(!(current >> RWLOCK_COUNT_SHIFT));

        if (!(current & RWLOCK_HAS_PARKED_MASK)) {
            if (a_cas(l, current, current & ~RWLOCK_IS_WRITE_HELD_BIT) == current)
                return;
            continue;
        }

        if (current & RWLOCK_HAS_PARKED_WRITE_BIT) {
            zunpark_one(RWLOCK_WRITE_PARK_ADDR(l), unlock_write_for_write_callback, l);
            return;
        }

        ZASSERT(current & RWLOCK_HAS_PARKED_READ_BIT);
        if (a_cas(l, current, current & ~(RWLOCK_IS_WRITE_HELD_BIT | RWLOCK_HAS_PARKED_READ_BIT))
            != current)
            continue;
        zunpark(RWLOCK_READ_PARK_ADDR(l), -1);
    }
}

static void unlock_read_for_write_callback(_Bool did_unpark_thread, _Bool may_have_more_threads, void* arg)
{
    volatile int* l = (volatile int*)arg;

    for (;;) {
        unsigned current = *l;
        
        unsigned read_count = current >> RWLOCK_COUNT_SHIFT;
        ZASSERT(read_count);
        ZASSERT(current & RWLOCK_HAS_PARKED_WRITE_BIT);
        
        unsigned new_value = (current & RWLOCK_BIT_MASK) | ((read_count - 1) << RWLOCK_COUNT_SHIFT);
        
        if (!may_have_more_threads)
            new_value &= ~RWLOCK_HAS_PARKED_WRITE_BIT;

        if (a_cas(l, current, new_value) == current)
            return;
    }
}

static void unlock_read(volatile int *l)
{
    for (;;) {
        unsigned current = *l;

        ZASSERT(!(current & RWLOCK_IS_WRITE_HELD_BIT));

        unsigned read_count = current >> RWLOCK_COUNT_SHIFT;
        ZASSERT(read_count);

        if (!(current & RWLOCK_HAS_PARKED_WRITE_BIT) || read_count > 1) {
            unsigned new_value = (current & RWLOCK_BIT_MASK) | ((read_count - 1) << RWLOCK_COUNT_SHIFT);
            if (a_cas(l, current, new_value) == current)
                return;
            continue;
        }

        ZASSERT(current & RWLOCK_HAS_PARKED_WRITE_BIT);
        /* NOTE: It's possible for the read count to go up between when we computed it and when the
           unpark happens.
           
           No big deal!
           
           We'll still drop the read count in that case, just not to zero, and we'll still unpark a
           thread. That thread will then find that the lock is still held and park itself again. */
        zunpark_one(RWLOCK_WRITE_PARK_ADDR(l), unlock_read_for_write_callback, l);
        return;
    }
}

int __pthread_rwlock_unlock(pthread_rwlock_t *rw)
{
    volatile int* l = &rw->__i;

    unsigned current = *l;
    if (current >> RWLOCK_COUNT_SHIFT) {
        unlock_read(l);
        return 0;
    }
    if (current & RWLOCK_IS_WRITE_HELD_BIT) {
        unlock_write(l);
        return 0;
    }
    return EPERM;
}

weak_alias(__pthread_rwlock_unlock, pthread_rwlock_unlock);
