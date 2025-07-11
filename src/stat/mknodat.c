#include <sys/stat.h>
#include "syscall.h"

int mknodat(int fd, const char *path, mode_t mode, dev_t dev)
{
	return zsys_mknodat(fd, path, mode, dev);
}
