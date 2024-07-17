#include <unistd.h>
#include "syscall.h"

pid_t getsid(pid_t pid)
{
	return zsys_getsid(pid);
}
