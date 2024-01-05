#include <elf.h>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "syscall.h"
#include "atomic.h"
#include "libc.h"
#include <errno.h>
#include <stdfil.h>

static void dummy(void) {}
weak_alias(dummy, _init);

static void dummy1(void *p) {}
weak_alias(dummy1, __init_ssp);

#define AUX_CNT 38

static void errno_handler(int errno_value)
{
    errno = errno_value;
}

#ifdef __GNUC__
__attribute__((__noinline__))
#endif
void __init_libc(char **envp, char *pn)
{
	size_t i, *auxv, aux[AUX_CNT] = { 0 };

        zregister_sys_errno_handler(errno_handler);
        
	__environ = envp;
	for (i=0; envp[i]; i++);
	libc.auxv = auxv = NULL;
	__hwcap = 0; // FIXME
	__sysinfo = 0; // FIXME;
        libc.page_size = 0; // FIXME;

        //if (!pn) pn = (void*)aux[AT_EXECFN];
	if (!pn) pn = "";
	__progname = __progname_full = pn;
	for (i=0; pn[i]; i++) if (pn[i]=='/') __progname = pn+i+1;

	//__init_tls(aux); FIXME
	//__init_ssp((void *)aux[AT_RANDOM]);

	//if (aux[AT_UID]==aux[AT_EUID] && aux[AT_GID]==aux[AT_EGID]
	//	&& !aux[AT_SECURE]) return;

//	struct pollfd pfd[3] = { {.fd=0}, {.fd=1}, {.fd=2} };
//	int r =
//#ifdef SYS_poll
//	__syscall(SYS_poll, pfd, 3, 0);
//#else
//	__syscall(SYS_ppoll, pfd, 3, &(struct timespec){0}, 0, _NSIG/8);
//#endif
//	if (r<0) a_crash();
//	for (i=0; i<3; i++) if (pfd[i].revents&POLLNVAL)
//		if (__sys_open("/dev/null", O_RDWR)<0)
//			a_crash();
	libc.secure = 1;
}

