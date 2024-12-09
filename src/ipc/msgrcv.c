#include <sys/msg.h>
#include "syscall.h"
#include "ipc.h"

ssize_t msgrcv(int q, void *m, size_t len, long type, int flag)
{
	return zsys_msgrcv(q, m, len, type, flag);
}
