#include <sys/membarrier.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include "pthread_impl.h"
#include "syscall.h"

static void dummy_0(void)
{
}

weak_alias(dummy_0, __tl_lock);
weak_alias(dummy_0, __tl_unlock);

static sem_t barrier_sem;

static void bcast_barrier(int s)
{
	sem_post(&barrier_sem);
}

int __membarrier(int cmd, int flags)
{
    zerror("membarrier not implemented");
    return -1;
}

void __membarrier_init(void)
{
}

weak_alias(__membarrier, membarrier);
