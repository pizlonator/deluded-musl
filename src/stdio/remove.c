#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"

int remove(const char *path)
{
	int r = zsys_unlink(path);
	if (r < 0 && errno == EISDIR) r = zsys_rmdir(path);
	return r;
}
