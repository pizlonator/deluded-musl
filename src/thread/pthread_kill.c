#include "pthread_impl.h"
#include "lock.h"

int pthread_kill(pthread_t t, int sig)
{
	return zthread_kill(t->zthread, sig) ? 0 : errno;
}
