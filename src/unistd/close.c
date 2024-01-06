#include <unistd.h>
#include <errno.h>
#include "aio_impl.h"
#include "syscall.h"
#include <stdfil.h>

static int dummy(int fd)
{
	return fd;
}

weak_alias(dummy, __aio_close);

int close(int fd)
{
	fd = __aio_close(fd);
        return zsys_close(fd);

        // WTF, do we need this thing about EINTR?
	//int r = __syscall_cp(SYS_close, fd);
	//if (r == -EINTR) r = 0;
	//return __syscall_ret(r);
}
