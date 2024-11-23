#include <sys/eventfd.h>
#include <unistd.h>
#include <errno.h>
#include "syscall.h"

int eventfd(unsigned int count, int flags)
{
	return zsys_eventfd(count, flags);
}

int eventfd_read(int fd, eventfd_t *value)
{
	return (sizeof(*value) == read(fd, value, sizeof(*value))) ? 0 : -1;
}

int eventfd_write(int fd, eventfd_t value)
{
	return (sizeof(value) == write(fd, &value, sizeof(value))) ? 0 : -1;
}
