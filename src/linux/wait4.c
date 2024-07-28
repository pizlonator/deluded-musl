#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>
#include "syscall.h"

pid_t wait4(pid_t pid, int *status, int options, struct rusage *ru)
{
	return zsys_wait4(pid, status, options, ru);
}
