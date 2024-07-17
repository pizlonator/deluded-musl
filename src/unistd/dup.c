#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

int dup(int fd)
{
	return zsys_dup(fd);
}
