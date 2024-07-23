#define _GNU_SOURCE
#include <sched.h>
#include <string.h>
#include "pthread_impl.h"
#include "syscall.h"

int sched_setaffinity(pid_t tid, size_t size, const cpu_set_t *set)
{
	return zsys_sched_setaffinity(tid, size, set);
}

int pthread_setaffinity_np(pthread_t td, size_t size, const cpu_set_t *set)
{
	if (sched_setaffinity(td->tid, size, set) < 0)
		return errno;
	return 0;
}

int sched_getaffinity(pid_t tid, size_t size, cpu_set_t *set)
{
	return zsys_sched_getaffinity(tid, size, set);
}

int pthread_getaffinity_np(pthread_t td, size_t size, cpu_set_t *set)
{
	if (sched_getaffinity(td->tid, size, set) < 0)
		return errno;
	return 0;
}
