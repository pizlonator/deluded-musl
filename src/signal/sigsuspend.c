#include <signal.h>
#include "syscall.h"

int sigsuspend(const sigset_t *mask)
{
	return zsys_sigsuspend(mask);
}
