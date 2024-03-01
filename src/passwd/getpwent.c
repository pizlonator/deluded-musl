#include "pwf.h"
#include <stdfil.h>

static FILE *f;
static char *line;
static struct passwd pw;
static size_t size;

void setpwent()
{
	if (f) fclose(f);
	f = 0;
}

weak_alias(setpwent, endpwent);

struct passwd *getpwent()
{
	struct passwd *res;
	if (!f) f = fopen("/etc/passwd", "rbe");
	if (!f) return 0;
	__getpwent_a(f, &pw, &line, &size, &res);
	return res;
}

struct passwd *getpwuid(uid_t uid)
{
    return (struct passwd*)zsys_getpwuid(uid);
}

struct passwd *getpwnam(const char *name)
{
    return (struct passwd*)zsys_getpwnam(name);
}
