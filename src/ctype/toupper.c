#include <ctype.h>

int toupper(int c)
{
	if (islower(c)) return c & 0x5f;
	return c;
}

int __toupper_l(int c, locale_t l)
{
	return toupper(c);
}

int toupper_l(int c, locale_t l)
{
    return __toupper_l(c, l);
}
