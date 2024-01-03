#include <ctype.h>

int isblank(int c)
{
	return (c == ' ' || c == '\t');
}

int __isblank_l(int c, locale_t l)
{
	return isblank(c);
}

int isblank_l(int c, locale_t l)
{
    return __isblank_l(c, l);
}
