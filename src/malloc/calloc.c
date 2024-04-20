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
	return zalloc(n); /* zalloc zeroes memory alraedy */
}
