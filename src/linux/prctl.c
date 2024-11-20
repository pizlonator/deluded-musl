#include <sys/prctl.h>
#include <stdarg.h>
#include "syscall.h"

__attribute__((__noinline__)) int prctl(int op, ...)
{
	return *(int*)zcall(zsys_prctl, zargs());
}
