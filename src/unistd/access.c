#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int access(const char *filename, int amode)
{
	return zsys_faccessat(AT_FDCWD, filename, amode, 0);
}
