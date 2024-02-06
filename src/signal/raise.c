#include <signal.h>
#include <stdint.h>
#include "syscall.h"
#include "pthread_impl.h"

int raise(int sig)
{
    zerror("raise not implemented");
    return 0;
	//sigset_t set;
	//__block_app_sigs(&set);
	//int ret = syscall(SYS_tkill, __pthread_self()->tid, sig);
	//__restore_sigs(&set);
	//return ret;
}
