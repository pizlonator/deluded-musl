#include <signal.h>
#include "syscall.h"
#include <stdfil.h>

int kill(pid_t pid, int sig)
{
	return zsys_kill(pid, sig);
}
