#include <sys/statvfs.h>
#include <sys/statfs.h>
#include "syscall.h"

static int __statfs(const char *path, struct statfs *buf)
{
	return zsys_statfs(path, buf);
}

static int __fstatfs(int fd, struct statfs *buf)
{
	return zsys_fstatfs(fd, buf);
}

weak_alias(__statfs, statfs);
weak_alias(__fstatfs, fstatfs);

int statvfs(const char *restrict path, struct statvfs *restrict buf)
{
	return zsys_statvfs(path, buf);
}

int fstatvfs(int fd, struct statvfs *buf)
{
	return zsys_fstatvfs(fd, buf);
}
