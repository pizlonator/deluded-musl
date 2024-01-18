#include <time.h>
#include <errno.h>
#include <stdint.h>
#include "syscall.h"
#include "atomic.h"
#include <stdfil.h>

#ifdef VDSO_CGT_SYM

static void *volatile vdso_func;

#ifdef VDSO_CGT32_SYM
static void *volatile vdso_func_32;
static int cgt_time32_wrap(clockid_t clk, struct timespec *ts)
{
	long ts32[2];
	int (*f)(clockid_t, long[2]) =
		(int (*)(clockid_t, long[2]))vdso_func_32;
	int r = f(clk, ts32);
	if (!r) {
		/* Fallback to syscalls if time32 overflowed. Maybe
		 * we lucked out and somehow migrated to a kernel with
		 * time64 syscalls available. */
		if (ts32[0] < 0) {
			a_cas_p(&vdso_func, (void *)cgt_time32_wrap, 0);
			return -ENOSYS;
		}
		ts->tv_sec = ts32[0];
		ts->tv_nsec = ts32[1];
	}
	return r;
}
#endif

static int cgt_init(clockid_t clk, struct timespec *ts)
{
	void *p = __vdsosym(VDSO_CGT_VER, VDSO_CGT_SYM);
#ifdef VDSO_CGT32_SYM
	if (!p) {
		void *q = __vdsosym(VDSO_CGT32_VER, VDSO_CGT32_SYM);
		if (q) {
			a_cas_p(&vdso_func_32, 0, q);
			p = cgt_time32_wrap;
		}
	}
#ifdef VDSO_CGT_WORKAROUND
	if (!__vdsosym(VDSO_CGT32_VER, VDSO_CGT32_SYM)) p = 0;
#endif
#endif
	int (*f)(clockid_t, struct timespec *) =
		(int (*)(clockid_t, struct timespec *))p;
	a_cas_p(&vdso_func, (void *)cgt_init, p);
	return f ? f(clk, ts) : -ENOSYS;
}

static void *volatile vdso_func = (void *)cgt_init;

#endif

int __clock_gettime(clockid_t clk, struct timespec *ts)
{
    return zsys_clock_gettime(clk, (unsigned long long*)ts);
}

weak_alias(__clock_gettime, clock_gettime);
