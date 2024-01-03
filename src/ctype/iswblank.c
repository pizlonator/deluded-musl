#include <wctype.h>
#include <ctype.h>

int iswblank(wint_t wc)
{
	return isblank(wc);
}

int __iswblank_l(wint_t c, locale_t l)
{
	return iswblank(c);
}

int iswblank_l(wint_t c, locale_t l)
{
    return __iswblank_l(c, l);
}

