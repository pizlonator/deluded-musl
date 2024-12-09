#include <sys/sem.h>
#include <stdarg.h>
#include <endian.h>
#include "syscall.h"
#include "ipc.h"

int semctl(int id, int num, int cmd, ...)
{
	return *(int*)zcall(zsys_semctl, zargs());
}
