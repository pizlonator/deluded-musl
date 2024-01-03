#include <ctype.h>

int isxdigit(int c)
{
	return isdigit(c) || ((unsigned)c|32)-'a' < 6;
}

int __isxdigit_l(int c, locale_t l)
{
	return isxdigit(c);
}

int isxdigit_l(int c, locale_t l)
{
    return __isxdigit_l(c, l);
}
