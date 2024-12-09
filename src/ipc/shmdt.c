#include <sys/shm.h>
#include "syscall.h"
#include "ipc.h"

int shmdt(const void *addr)
{
	return zsys_shmdt(addr);
}
