#include <sys/sem.h>
#include <limits.h>
#include <errno.h>
#include "syscall.h"
#include "ipc.h"

int semget(key_t key, int n, int fl)
{
	return zsys_semget(key, n, fl);
}
