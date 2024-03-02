#include <unistd.h>
#include "syscall.h"

int getgroups(int count, gid_t list[])
{
	return zsys_getgroups(count, list);
}
