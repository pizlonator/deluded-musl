#define _GNU_SOURCE
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include "syscall.h"

int fcntl(int fd, int cmd, ...)
{
	va_list ap;
	va_start(ap, cmd);
	int result;
	switch (cmd) {
	case F_OFD_GETLK:
	case F_OFD_SETLK:
	case F_OFD_SETLKW:
	case F_GETLK:
	case F_SETLK:
	case F_SETLKW:
	case F_GET_RW_HINT:
	case F_SET_RW_HINT:
	case F_GET_FILE_RW_HINT:
	case F_SET_FILE_RW_HINT:
	case F_GETOWN_EX:
	case F_SETOWN_EX:
	case F_GETOWNER_UIDS:
		result = zsys_fcntl(fd, cmd, va_arg(ap, void*));
		break;
	case F_DUPFD_CLOEXEC:
	case F_SETLEASE:
	case F_NOTIFY:
	case F_SETPIPE_SZ:
	case F_ADD_SEALS:
	case F_DUPFD:
	case F_SETFD:
	case F_SETFL:
	case F_SETOWN:
	case F_SETSIG:
		result = zsys_fcntl(fd, cmd, va_arg(ap, int));
		break;
	case F_GETLEASE:
	case F_GETPIPE_SZ:
	case F_GET_SEALS:
	case F_GETFD:
	case F_GETFL:
	case F_GETOWN:
	case F_GETSIG:
		result = zsys_fcntl(fd, cmd);
		break;
	default:
		errno = EINVAL;
		result = -1;
		break;
	}
	va_end(ap);
	return result;
}
