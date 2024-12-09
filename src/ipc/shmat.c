#include <sys/shm.h>
#include "syscall.h"
#include "ipc.h"

void *shmat(int id, const void *addr, int flag)
{
	return zsys_shmat(id, addr, flag);
}
