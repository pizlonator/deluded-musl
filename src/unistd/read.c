#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

ssize_t read(int fd, void *buf, size_t count)
{
	return zsys_read(fd, buf, count);
}
