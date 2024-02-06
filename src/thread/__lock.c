#include "pthread_impl.h"
#include <stdfil.h>

/* Implements the wtf-lock, which just uses two bits. */
static const int is_held_bit = 1;
static const int has_parked_bit = 1;

void __lock(volatile int *l)
{
    if (a_cas(l, 0, is_held_bit) == 0)
        return;

    unsigned spin_count = 0;
    for (;;) {
        int current = *l;

        // Barge!
        if (!(current & is_held_bit)) {
            if (a_cas(l, current, current | is_held_bit) == current)
                return;
            continue;
        }

        if (!(current & has_parked_bit) && spin_count < SPIN_LIMIT) {
            spin_count++;
            zsys_sched_yield();
            continue;
        }

        if (!(current & has_parked_bit)) {
            int new_value = current | has_parked_bit;
            if (a_cas(l, current, new_value) != current)
                continue;
            current = new_value;
        }

        ZASSERT(current == (is_held_bit | has_parked_bit));

        zcompare_and_park(l, is_held_bit | has_parked_bit, 1. / 0.);
    }
}

int __trylock(volatile int *l)
{
    for (;;) {
        int current = *l;
        if (current & is_held_bit)
            return 0;
        if (a_cas(l, current, current | is_held_bit) == current)
            return 1;
    }
}

static void unlock_callback(_Bool did_unpark_thread, _Bool may_have_more_threads, void* arg)
{
    volatile int *l = (volatile int*)arg;
    int new_value;

    new_value = 0;
    if (may_have_more_threads)
        new_value |= has_parked_bit;

    ZASSERT(*l == (is_held_bit | has_parked_bit));
    ZASSERT(a_cas(l, is_held_bit | has_parked_bit, new_value) == (is_held_bit | has_parked_bit));
}

void __unlock(volatile int *l)
{
    if (a_cas(l, is_held_bit, 0) == is_held_bit)
        return;

    for (;;) {
        int old_value = *l;
        ZASSERT(old_value == is_held_bit || old_value == (is_held_bit | has_parked_bit));

        if (old_value == is_held_bit) {
            if (a_cas(l, is_held_bit, 0) == is_held_bit)
                return;
            continue;
        }

        ZASSERT(old_value == (is_held_bit | has_parked_bit));
        zunpark_one(l, unlock_callback, l);
        return;
    }
}

