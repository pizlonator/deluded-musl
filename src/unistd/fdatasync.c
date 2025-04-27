#include <unistd.h>
#include "syscall.h"

int fdatasync(int fd)
{
	return zsys_fdatasync(fd);
}
