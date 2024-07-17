#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"

int pipe2(int fd[2], int flag)
{
	if (!flag) return pipe(fd);
	if (flag & ~(O_CLOEXEC|O_NONBLOCK)) return __syscall_ret(-EINVAL);
	int ret = pipe(fd);
	if (ret) return ret;
	if (flag & O_CLOEXEC) {
		zsys_fcntl(fd[0], F_SETFD, FD_CLOEXEC);
		zsys_fcntl(fd[1], F_SETFD, FD_CLOEXEC);
	}
	if (flag & O_NONBLOCK) {
		zsys_fcntl(fd[0], F_SETFL, O_NONBLOCK);
		zsys_fcntl(fd[1], F_SETFL, O_NONBLOCK);
	}
	return 0;
}
