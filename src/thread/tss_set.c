#include "pthread_impl.h"
#include <threads.h>
#include <stdfil.h>

int tss_set(tss_t k, void *x)
{
    ZASSERT(zthread_setspecific(k, x));
    return thrd_success;
}
