#include <sys/sem.h>
#include "syscall.h"
#include "ipc.h"

int semop(int id, struct sembuf *buf, size_t n)
{
	return zsys_semop(id, buf, n);
}
