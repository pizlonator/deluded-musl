#define _GNU_SOURCE
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include "syscall.h"
#include <stdfil.h>

int fcntl(int fd, int cmd, ...)
{
	va_list ap;
        int res;
	va_start(ap, cmd);
        // FIXME: I should totally add varargs forwarding support to the stdfil API, it would be
        // hella fucking useful.
        switch (cmd) {
        case F_GETLK:
        case F_SETLK:
        case F_SETLKW:
            res = zsys_fcntl(fd, cmd, va_arg(ap, void*));
            break;
        case F_DUPFD:
        case F_SETFD:
        case F_SETFL:
        case F_SETOWN:
        case F_DUPFD_CLOEXEC:
            res = zsys_fcntl(fd, cmd, va_arg(ap, int));
            break;
        default:
            res = zsys_fcntl(fd, cmd);
            break;
        }
	va_end(ap);
        return res;
}
