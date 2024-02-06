#include <threads.h>
#include <pthread.h>
#include <stdfil.h>

int cnd_broadcast(cnd_t *c)
{
    zerror("cnd not implemented");
    return 0;
	/* This internal function never fails, and always returns zero,
	 * which matches the value thrd_success is defined with. */
	//return __private_cond_signal((pthread_cond_t *)c, -1);
}
