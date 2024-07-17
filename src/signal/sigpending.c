#include <signal.h>
#include "syscall.h"

int sigpending(sigset_t *set)
{
	return zsys_sigpending(set);
}
