#include <elf.h>
#include <errno.h>
#include <pizlonated_runtime.h>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "syscall.h"
#include "atomic.h"
#include "dynlink.h"
#include "libc.h"

static void dummy(void) {}
weak_alias(dummy, _init);

static void dummy1(void *p) {}
weak_alias(dummy1, __init_ssp);

#define AUX_CNT 38

static void errno_handler(int errno_value)
{
	errno = errno_value;
}

static void dlerror_handler(const char* str)
{
	__dl_seterr("%s", str);
}

#ifdef __GNUC__
__attribute__((__noinline__))
#endif
void __init_libc(char **envp, char *pn, size_t *auxv)
{
	size_t i, aux[AUX_CNT] = { 0 };
	__environ = envp;
	libc.auxv = auxv;
	for (i=0; auxv[i]; i+=2) if (auxv[i]<AUX_CNT) aux[auxv[i]] = auxv[i+1];
	__hwcap = aux[AT_HWCAP];
	if (aux[AT_SYSINFO]) __sysinfo = aux[AT_SYSINFO];
	libc.page_size = aux[AT_PAGESZ];

	if (!pn) pn = (void*)aux[AT_EXECFN];
	if (!pn) pn = "";
	__progname = __progname_full = pn;
	for (i=0; pn[i]; i++) if (pn[i]=='/') __progname = pn+i+1;

	__init_tls(aux);

	zregister_sys_errno_handler(errno_handler);
	zregister_sys_dlerror_handler(dlerror_handler);
	
	__init_ssp((void *)aux[AT_RANDOM]);

	if (aux[AT_UID]==aux[AT_EUID] && aux[AT_GID]==aux[AT_EGID]
		&& !aux[AT_SECURE]) return;

	struct pollfd pfd[3] = { {.fd=0}, {.fd=1}, {.fd=2} };
	int r = zsys_poll(pfd, 3, 0);
	if (r<0) a_crash();
	for (i=0; i<3; i++) if (pfd[i].revents&POLLNVAL)
		if (zsys_open("/dev/null", O_RDWR)<0)
			a_crash();
	libc.secure = 1;
}

void __libc_start_main(int (*main)(int,char **,char **), int argc, char **argv,
                       char **envp, size_t *auxv)
{
	/* External linkage, and explicit noinline attribute if available,
	 * are used to prevent the stack frame used during init from
	 * persisting for the entire process lifetime. */
	__init_libc(envp, argv[0], auxv);

	zrun_deferred_global_ctors();

	/* Pass control to the application */
	exit(main(argc, argv, envp));
}

