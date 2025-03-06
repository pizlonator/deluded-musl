#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "syscall.h"
#include "pthread_impl.h"

int sigqueue(pid_t pid, int sig, const union sigval value)
{
	return zsys_sigqueue(pid, sig, value.sival_ptr);
}
