#define a_ll_p a_ll_p
static inline void *a_ll_p(volatile void *p)
{
	void *v;
	__asm__ __volatile__ ("ldaxr %0, %1" : "=r"(v) : "Q"(*(void *volatile *)p));
	return v;
}

#define a_sc_p a_sc_p
static inline int a_sc_p(volatile int *p, void *v)
{
	int r;
	__asm__ __volatile__ ("stlxr %w0,%2,%1" : "=&r"(r), "=Q"(*(void *volatile *)p) : "r"(v) : "memory");
	return !r;
}

#define a_cas_p a_cas_p
static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	void *old;
	do {
		old = a_ll_p(p);
		if (old != t) {
			zfence();
			break;
		}
	} while (!a_sc_p(p, s));
	return old;
}

