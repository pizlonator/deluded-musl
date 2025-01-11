#include <sys/file.h>
#include "syscall.h"

int flock(int fd, int op)
{
	return zsys_flock(fd, op);
}
