#include <sys/msg.h>
#include "syscall.h"
#include "ipc.h"

int msgget(key_t k, int flag)
{
	return zsys_msgget(k, flag);
}
