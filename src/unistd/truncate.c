#include <unistd.h>
#include "syscall.h"

int truncate(const char *path, off_t length)
{
	return zsys_truncate(path, length);
}
