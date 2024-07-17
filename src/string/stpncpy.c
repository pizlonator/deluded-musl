#include <string.h>
#include <stdint.h>
#include <limits.h>

#define ALIGN (sizeof(size_t)-1)
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

char *__stpncpy(char *restrict d, const char *restrict s, size_t n)
{
	for (; n && (*d=*s); n--, s++, d++);
tail:
	memset(d, 0, n);
	return d;
}

weak_alias(__stpncpy, stpncpy);

