#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

ssize_t write(int fd, const void *buf, size_t count)
{
	return zsys_write(fd, buf, count);
}
