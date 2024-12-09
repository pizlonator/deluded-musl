#define _GNU_SOURCE
#include <sys/sem.h>
#include <errno.h>
#include "syscall.h"
#include "ipc.h"

int semtimedop(int id, struct sembuf *buf, size_t n, const struct timespec *ts)
{
	return zsys_semtimedop(id, buf, n, ts);
}
