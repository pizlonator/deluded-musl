#include <unistd.h>
#include "syscall.h"

int symlinkat(const char *existing, int fd, const char *new)
{
	return zsys_symlinkat(existing, fd, new);
}
