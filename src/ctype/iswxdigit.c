#include <wctype.h>

int iswxdigit(wint_t wc)
{
	return (unsigned)(wc-'0') < 10 || (unsigned)((wc|32)-'a') < 6;
}

int __iswxdigit_l(wint_t c, locale_t l)
{
	return iswxdigit(c);
}

int iswcdigit_l(wint_t c, locale_t l)
{
    return __iswxdigit_l(c, l);
}
