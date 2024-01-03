#include <ctype.h>
#undef isspace

int isspace(int c)
{
	return c == ' ' || (unsigned)c-'\t' < 5;
}

int __isspace_l(int c, locale_t l)
{
	return isspace(c);
}

int isspace_l(int c, locale_t l)
{
    return __isspace_l(c, l);
}

