#ifndef _ATOMIC_H
#define _ATOMIC_H

#include <stdint.h>

#include <stdfil.h>
#include "atomic_arch.h"

#ifndef a_barrier
#define a_barrier a_barrier
static inline void a_barrier(void) { zfence(); }
#endif

#ifndef a_cas
#define a_cas a_cas
static inline int a_cas(volatile int *p, int t, int s)
{
    __c11_atomic_compare_exchange_strong((_Atomic int*)p, &t, s, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    return t;
}
#endif

#ifndef a_swap
#define a_swap a_swap
static inline int a_swap(volatile int *p, int v)
{
    return __c11_atomic_exchange((_Atomic int*)p, v, __ATOMIC_SEQ_CST);
}
#endif

#ifndef a_fetch_add
#define a_fetch_add a_fetch_add
static inline int a_fetch_add(volatile int *p, int v)
{
    return __c11_atomic_fetch_add((_Atomic int*)p, v, __ATOMIC_SEQ_CST);
}
#endif

#ifndef a_fetch_and
#define a_fetch_and a_fetch_and
static inline int a_fetch_and(volatile int *p, int v)
{
    return __c11_atomic_fetch_and((_Atomic int*)p, v, __ATOMIC_SEQ_CST);
}
#endif

#ifndef a_fetch_or
#define a_fetch_or a_fetch_or
static inline int a_fetch_or(volatile int *p, int v)
{
    return __c11_atomic_fetch_or((_Atomic int*)p, v, __ATOMIC_SEQ_CST);
}
#endif

#ifdef a_ll_p

#ifndef a_cas_p
#define a_cas_p a_cas_p
static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	void *old;
	a_pre_llsc();
	do old = a_ll_p(p);
	while (old==t && !a_sc_p(p, s));
	a_post_llsc();
	return old;
}
#endif

#endif

#ifndef a_cas
#error missing definition of a_cas
#endif

#ifndef a_swap
#define a_swap a_swap
static inline int a_swap(volatile int *p, int v)
{
	int old;
	do old = *p;
	while (a_cas(p, old, v) != old);
	return old;
}
#endif

#ifndef a_fetch_add
#define a_fetch_add a_fetch_add
static inline int a_fetch_add(volatile int *p, int v)
{
	int old;
	do old = *p;
	while (a_cas(p, old, (unsigned)old+v) != old);
	return old;
}
#endif

#ifndef a_fetch_and
#define a_fetch_and a_fetch_and
static inline int a_fetch_and(volatile int *p, int v)
{
	int old;
	do old = *p;
	while (a_cas(p, old, old&v) != old);
	return old;
}
#endif
#ifndef a_fetch_or
#define a_fetch_or a_fetch_or
static inline int a_fetch_or(volatile int *p, int v)
{
	int old;
	do old = *p;
	while (a_cas(p, old, old|v) != old);
	return old;
}
#endif

#ifndef a_and
#define a_and a_and
static inline void a_and(volatile int *p, int v)
{
	a_fetch_and(p, v);
}
#endif

#ifndef a_or
#define a_or a_or
static inline void a_or(volatile int *p, int v)
{
	a_fetch_or(p, v);
}
#endif

#ifndef a_inc
#define a_inc a_inc
static inline void a_inc(volatile int *p)
{
	a_fetch_add(p, 1);
}
#endif

#ifndef a_dec
#define a_dec a_dec
static inline void a_dec(volatile int *p)
{
	a_fetch_add(p, -1);
}
#endif

#ifndef a_store
#define a_store a_store
static inline void a_store(volatile int *p, int v)
{
#ifdef a_barrier
	a_barrier();
	*p = v;
	a_barrier();
#else
	a_swap(p, v);
#endif
}
#endif

#ifndef a_barrier
#define a_barrier a_barrier
static void a_barrier()
{
	volatile int tmp = 0;
	a_cas(&tmp, 0, 0);
}
#endif

#ifndef a_spin
#define a_spin a_barrier
#endif

#ifndef a_and_64
#define a_and_64 a_and_64
static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	union { uint64_t v; uint32_t r[2]; } u = { v };
	if (u.r[0]+1) a_and((int *)p, u.r[0]);
	if (u.r[1]+1) a_and((int *)p+1, u.r[1]);
}
#endif

#ifndef a_or_64
#define a_or_64 a_or_64
static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	union { uint64_t v; uint32_t r[2]; } u = { v };
	if (u.r[0]) a_or((int *)p, u.r[0]);
	if (u.r[1]) a_or((int *)p+1, u.r[1]);
}
#endif

#ifndef a_cas_p
typedef char a_cas_p_undefined_but_pointer_not_32bit[-sizeof(char) == 0xffffffff ? 1 : -1];
#define a_cas_p a_cas_p
static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	return (void *)a_cas((volatile int *)p, (int)t, (int)s);
}
#endif

#ifndef a_or_l
#define a_or_l a_or_l
static inline void a_or_l(volatile void *p, long v)
{
	if (sizeof(long) == sizeof(int)) a_or(p, v);
	else a_or_64(p, v);
}
#endif

#ifndef a_crash
#define a_crash a_crash
static inline void a_crash()
{
	*(volatile char *)0=0;
}
#endif

#ifndef a_ctz_32
#define a_ctz_32 a_ctz_32
static inline int a_ctz_32(uint32_t x)
{
    return __builtin_ctz(x);
}
#endif

#ifndef a_ctz_64
#define a_ctz_64 a_ctz_64
static inline int a_ctz_64(uint64_t x)
{
    return __builtin_ctzll(x);
}
#endif

static inline int a_ctz_l(unsigned long x)
{
	return (sizeof(long) < 8) ? a_ctz_32(x) : a_ctz_64(x);
}

#ifndef a_clz_64
#define a_clz_64 a_clz_64
static inline int a_clz_64(uint64_t x)
{
    return __builtin_clzll(x);
}
#endif

#ifndef a_clz_32
#define a_clz_32 a_clz_32
static inline int a_clz_32(uint32_t x)
{
    return __builtin_clz(x);
}
#endif

#endif
