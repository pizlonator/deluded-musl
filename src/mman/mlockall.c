#include <sys/mman.h>
#include "syscall.h"

int mlockall(int flags)
{
	return zsys_mlockall(flags);
}
