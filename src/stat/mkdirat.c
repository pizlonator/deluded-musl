#include <sys/stat.h>
#include "syscall.h"

int mkdirat(int fd, const char *path, mode_t mode)
{
	return zsys_mkdirat(fd, path, mode);
}
