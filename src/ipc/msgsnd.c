#include <sys/msg.h>
#include "syscall.h"
#include "ipc.h"

int msgsnd(int q, const void *m, size_t len, int flag)
{
	return zsys_msgsnd(q, m, len, flag);
}
