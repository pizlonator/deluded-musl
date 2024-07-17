#include <string.h>
#include <stdint.h>
#include <limits.h>

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

char *__stpcpy(char *restrict d, const char *restrict s)
{
	for (; (*d=*s); s++, d++);

	return d;
}

weak_alias(__stpcpy, stpcpy);
