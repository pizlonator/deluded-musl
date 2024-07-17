#define _GNU_SOURCE
#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

int chroot(const char *path)
{
	return zsys_chroot(path);
}
