#include <unistd.h>
#include "syscall.h"

int unlinkat(int fd, const char *path, int flag)
{
	return zsys_unlinkat(fd, path, flag);
}
