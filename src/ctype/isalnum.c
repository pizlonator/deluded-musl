#include <ctype.h>

int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

int __isalnum_l(int c, locale_t l)
{
	return isalnum(c);
}

int isalnum_l(int c, locale_t l)
{
    return __isalnum_l(c, l);
}
