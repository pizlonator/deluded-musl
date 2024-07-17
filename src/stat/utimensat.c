#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include "syscall.h"

int utimensat(int fd, const char *path, const struct timespec times[2], int flags)
{
	return zsys_utimensat(fd, path, times, flags);
}
