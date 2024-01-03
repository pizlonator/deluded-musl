#include <ctype.h>

int tolower(int c)
{
	if (isupper(c)) return c | 32;
	return c;
}

int __tolower_l(int c, locale_t l)
{
	return tolower(c);
}

int tolower_l(int c, locale_t l)
{
    return __tolower_l(c, l);
}


