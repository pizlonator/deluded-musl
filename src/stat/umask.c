#include <sys/stat.h>
#include "syscall.h"
#include <stdfil.h>

mode_t umask(mode_t mode)
{
	return zsys_umask(mode);
}
