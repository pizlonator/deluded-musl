#define _GNU_SOURCE
#include <utmpx.h>
#include <stddef.h>
#include <errno.h>
#include <stdfil.h>

void endutxent(void)
{
    return zsys_endutxent();
}

void setutxent(void)
{
    return zsys_setutxent();
}

struct utmpx *getutxent(void)
{
    return zsys_getutxent();
}

struct utmpx *getutxid(const struct utmpx *ut)
{
    return zsys_getutxid(ut);
}

struct utmpx *getutxline(const struct utmpx *ut)
{
    return zsys_getutxline(ut);
}

struct utmpx *pututxline(const struct utmpx *ut)
{
    return zsys_pututxline(ut);
}

void updwtmpx(const char *f, const struct utmpx *u)
{
}

static int __utmpxname(const char *f)
{
	errno = ENOTSUP;
	return -1;
}

struct lastlogx *getlastlogx(uid_t uid, struct lastlogx *lastlogx)
{
    return zsys_getlastlogx(uid, lastlogx);
}

struct lastlogx *getlastlogxbyname(const char* name, struct lastlogx *lastlogx)
{
    return zsys_getlastlogxbyname(name, lastlogx);
}

weak_alias(endutxent, endutent);
weak_alias(setutxent, setutent);
weak_alias(getutxent, getutent);
weak_alias(getutxid, getutid);
weak_alias(getutxline, getutline);
weak_alias(pututxline, pututline);
weak_alias(updwtmpx, updwtmp);
weak_alias(__utmpxname, utmpname);
weak_alias(__utmpxname, utmpxname);
