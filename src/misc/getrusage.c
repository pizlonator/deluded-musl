#include <sys/resource.h>
#include <string.h>
#include <errno.h>
#include "syscall.h"

int getrusage(int who, struct rusage *ru)
{
	return zsys_getrusage(who, ru);
}
