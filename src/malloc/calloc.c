#include <stdlib.h>
#include <stdfil.h>
#include <errno.h>

void *calloc(size_t m, size_t n)
{
	if (n && m > (size_t)-1/n) {
		errno = ENOMEM;
		return 0;
	}
	n *= m;
	void *p = malloc(n);
        __builtin_memset(p, 0, n);
	return p;
}
