#include <sys/shm.h>
#include <stdint.h>
#include "syscall.h"
#include "ipc.h"

int shmget(key_t key, size_t size, int flag)
{
	return zsys_shmget(key, size, flag);
}
