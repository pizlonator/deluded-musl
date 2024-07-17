#include <fcntl.h>
#include <stdarg.h>
#include "syscall.h"
#include <stdfil.h>

int open(const char *filename, int flags, ...)
{
	mode_t mode = 0;

	if ((flags & O_CREAT) || (flags & O_TMPFILE) == O_TMPFILE) {
		va_list ap;
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);
	}

	int fd = zsys_open(filename, flags, mode);
	if (fd>=0 && (flags & O_CLOEXEC))
		zsys_fcntl(fd, F_SETFD, FD_CLOEXEC);

	return fd;
}
