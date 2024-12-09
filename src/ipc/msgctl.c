#include <sys/msg.h>
#include <endian.h>
#include "syscall.h"
#include "ipc.h"

int msgctl(int q, int cmd, struct msqid_ds *buf)
{
	return zsys_msgctl(q, cmd, buf);
}
