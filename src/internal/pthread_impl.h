#ifndef _PTHREAD_IMPL_H
#define _PTHREAD_IMPL_H

#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <sys/mman.h>
#include "libc.h"
#include "syscall.h"
#include "atomic.h"
#include "futex.h"
#include <pizlonated_runtime.h>

#include "pthread_arch.h"

#define pthread __pthread

struct pthread {
	/* Part 1 -- these fields may be external or
	 * internal (accessed via asm) ABI. Do not change. */
	struct pthread *self;
#ifndef TLS_ABOVE_TP
	uintptr_t *dtv;
#endif
	struct pthread *prev, *next; /* non-ABI */
	uintptr_t sysinfo;
#ifndef TLS_ABOVE_TP
#ifdef CANARY_PAD
	uintptr_t canary_pad;
#endif
	uintptr_t canary;
#endif

	/* Part 2 -- implementation details, non-ABI. */
	//int tid;
	int errno_val;
	volatile int detach_state;
	volatile int cancel;
	volatile unsigned char canceldisable, cancelasync;
	unsigned char tsd_used:1;
	unsigned char dlerror_flag:1;
	unsigned char *map_base;
	size_t map_size;
	void *stack;
	size_t stack_size;
	size_t guard_size;
	void *result;
	struct __ptcb *cancelbuf;
	void **tsd;
	struct {
		volatile void *volatile head;
		long off;
		volatile void *volatile pending;
	} robust_list;
	int h_errno_val;
	volatile int timer_id;
	locale_t locale;
	volatile int killlock[1];
	char *dlerror_buf;
	void *stdio_locks;

	/* Part 3 -- the positions of these fields relative to
	 * the end of the structure is external and internal ABI. */
#ifdef TLS_ABOVE_TP
	uintptr_t canary;
	uintptr_t *dtv;
#endif
};

typedef struct {
    void* value;
    unsigned long long version;
} thread_local_data;

typedef struct {
    int the_errno;
    locale_t locale;
    thread_local_data* thread_locals;
    char* dlerror_string;
    int dlerror_flag;
} internal_thread_data;

typedef struct {
    void (*destructor)(void* arg);
    int is_active;
    unsigned long long version;
    size_t next_free_index;
} thread_local_descriptor;

extern hidden volatile int thread_local_lock;
extern hidden thread_local_descriptor* thread_locals;
extern hidden size_t next_free_descriptor;

hidden internal_thread_data* get_internal_thread_data(void);
hidden void set_new_internal_thread_data(void);
hidden void destroy_internal_thread_data(void);

enum {
	DT_EXITED = 0,
	DT_EXITING,
	DT_JOINABLE,
	DT_DETACHED,
};

#define __SU (sizeof(size_t)/sizeof(int))

#define _a_stacksize __u.__s[0]
#define _a_guardsize __u.__s[1]
#define _a_stackaddr __u.__s[2]
#define _a_detach __u.__i[3*__SU+0]
#define _a_sched __u.__i[3*__SU+1]
#define _a_policy __u.__i[3*__SU+2]
#define _a_prio __u.__i[3*__SU+3]
#define _b_lock __u.__vi[0]
#define _b_waiters __u.__vi[1]
#define _b_limit __u.__i[2]
#define _b_count __u.__vi[3]
#define _b_waiters2 __u.__vi[4]
#define _b_inst __u.__p[3]

// This magic number was good enough for Jikes RVM and WebKit, so it's going to be good enough
// for Deluge, too.
#define SPIN_LIMIT 40u

#define RWLOCK_IS_WRITE_HELD_BIT     1u
#define RWLOCK_IS_WRITE_SPINNING_BIT 2u
#define RWLOCK_HAS_PARKED_WRITE_BIT  4u
#define RWLOCK_HAS_PARKED_READ_BIT   8u
#define RWLOCK_HAS_PARKED_MASK       12u
#define RWLOCK_BIT_MASK              15u
#define RWLOCK_COUNT_SHIFT           4u
#define RWLOCK_READ_PARK_ADDR(l)     (l)
#define RWLOCK_WRITE_PARK_ADDR(l)    ((int*)((char*)(l) + 1))

#ifndef TP_OFFSET
#define TP_OFFSET 0
#endif

#ifndef DTP_OFFSET
#define DTP_OFFSET 0
#endif

#define __pthread_self() ((pthread_t)zthread_self())

#ifndef tls_mod_off_t
#define tls_mod_off_t size_t
#endif

#define SIGTIMER 32
#define SIGCANCEL 33
#define SIGSYNCCALL 34

#define SIGALL_SET ((sigset_t *)(const unsigned long long [2]){ -1,-1 })
#define SIGPT_SET \
	((sigset_t *)(const unsigned long [_NSIG/8/sizeof(long)]){ \
	[sizeof(long)==4] = 3UL<<(32*(sizeof(long)>4)) })
#define SIGTIMER_SET \
	((sigset_t *)(const unsigned long [_NSIG/8/sizeof(long)]){ \
	 0x80000000 })

void *__tls_get_addr(tls_mod_off_t *);
hidden int __init_tp(void *);
hidden void *__copy_tls(unsigned char *);
hidden void __reset_tls();

hidden void __membarrier_init(void);
hidden void __dl_thread_cleanup(void);
hidden void __testcancel();
hidden void __do_cleanup_push(struct __ptcb *);
hidden void __do_cleanup_pop(struct __ptcb *);
hidden void __pthread_tsd_run_dtors();

hidden void __pthread_key_delete_synccall(void (*)(void *), void *);
hidden int __pthread_key_delete_impl(pthread_key_t);

extern hidden volatile size_t __pthread_tsd_size;
extern hidden void *__pthread_tsd_main[];
extern hidden volatile int __eintr_valid_flag;

hidden int __clone(int (*)(void *), void *, int, void *, ...);
hidden int __set_thread_area(void *);
hidden int __libc_sigaction(int, const struct sigaction *, struct sigaction *);
hidden void __unmapself(void *, size_t);

static inline double get_milliseconds(const struct timespec *ts)
{
    if (!ts)
        return 1. / 0.;
    return ts->tv_sec * 1000. * 1000. + ts->tv_nsec / 1000.;
}

hidden int __timedwait(volatile int *, int, clockid_t, const struct timespec *, int);
hidden int __timedwait_cp(volatile int *, int, clockid_t, const struct timespec *, int);
hidden void __wait(volatile int *, volatile int *, int, int);
static inline void __wake(volatile void *addr, int cnt, int priv)
{
    ZASSERT(priv);
    zunpark(addr, cnt);
}
static inline void __futexwait(volatile void *addr, int val, int priv)
{
    ZASSERT(priv);
    zcompare_and_park(addr, val, 1. / 0.);
}

hidden void __acquire_ptc(void);
hidden void __release_ptc(void);
hidden void __inhibit_ptc(void);

extern hidden volatile int __abort_lock[1];

extern hidden unsigned __default_stacksize;
extern hidden unsigned __default_guardsize;

#define DEFAULT_STACK_SIZE 131072
#define DEFAULT_GUARD_SIZE 8192

#define DEFAULT_STACK_MAX (8<<20)
#define DEFAULT_GUARD_MAX (1<<20)

#define __ATTRP_C11_THREAD ((void*)(uintptr_t)-1)

static inline int __mutex_lock_wrapper(pthread_mutex_t* m, int (*lock_impl)(pthread_mutex_t* m))
{
    if (m->__recurse_count != UINT_MAX && m->__tid == zthread_self_id()) {
        ZASSERT(m->__recurse_count);
        if (m->__recurse_count + 1 == UINT_MAX)
            return EAGAIN;
        m->__recurse_count++;
        return 0;
    }
    int result = lock_impl(m);
    if (result)
        return result;
    if (m->__recurse_count != UINT_MAX) {
        ZASSERT(!m->__recurse_count);
        m->__tid = zthread_self_id();
        m->__recurse_count = 1;
    }
    return 0;
}

#endif
