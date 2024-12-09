#include <sys/shm.h>
#include <endian.h>
#include "syscall.h"
#include "ipc.h"

int shmctl(int id, int cmd, struct shmid_ds *buf)
{
	return zsys_shmctl(id, cmd, buf);
}
