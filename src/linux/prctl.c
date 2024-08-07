#include <sys/prctl.h>
#include <stdarg.h>
#include "syscall.h"

int prctl(int op, ...)
{
	return (int)zcall_int(zsys_prctl, zargs());
}
