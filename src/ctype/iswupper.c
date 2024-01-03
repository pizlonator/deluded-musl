#include <wctype.h>

int iswupper(wint_t wc)
{
	return towlower(wc) != wc;
}

int __iswupper_l(wint_t c, locale_t l)
{
	return iswupper(c);
}

int iswupper_l(wint_t c, locale_t l)
{
    return __iswupper_l(c, l);
}
