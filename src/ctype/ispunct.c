#include <ctype.h>

int ispunct(int c)
{
	return isgraph(c) && !isalnum(c);
}

int __ispunct_l(int c, locale_t l)
{
	return ispunct(c);
}

int ispunct_l(int c, locale_t l)
{
    return __ispunct_l(c, l);
}
