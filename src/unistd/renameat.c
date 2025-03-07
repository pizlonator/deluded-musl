#include <stdio.h>
#include "syscall.h"

int renameat(int oldfd, const char *old, int newfd, const char *new)
{
	return zsys_renameat(oldfd, old, newfd, new);
}
