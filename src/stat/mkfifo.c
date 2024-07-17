#include <sys/stat.h>
#include <pizlonated_musl_syscalls.h>

int mkfifo(const char *path, mode_t mode)
{
	return zsys_mkfifo(path, mode);
}
