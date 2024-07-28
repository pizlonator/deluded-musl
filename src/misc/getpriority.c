#include <sys/resource.h>
#include "syscall.h"

int getpriority(int which, id_t who)
{
	return zsys_getpriority(which, who);
}
