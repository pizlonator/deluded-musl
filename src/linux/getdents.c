#define _BSD_SOURCE
#include <dirent.h>
#include <limits.h>
#include "syscall.h"

int getdents(int fd, struct dirent *buf, size_t len)
{
	return zsys_getdents(fd, buf, len);
}
