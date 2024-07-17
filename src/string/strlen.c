#include <string.h>
#include <stdint.h>
#include <limits.h>

size_t strlen(const char *s)
{
	const char *a = s;
	for (; *s; s++);
	return s-a;
}
