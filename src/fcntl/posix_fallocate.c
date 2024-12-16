#include <fcntl.h>
#include "syscall.h"

int posix_fallocate(int fd, off_t base, off_t len)
{
	return zsys_posix_fallocate(fd, base, len);
}
