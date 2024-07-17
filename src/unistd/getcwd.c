#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include "syscall.h"
#include <stdfil.h>

char *getcwd(char *buf, size_t size)
{
	char tmp[buf ? 1 : PATH_MAX];
	if (!buf) {
		buf = tmp;
		size = sizeof tmp;
	} else if (!size) {
		errno = EINVAL;
		return 0;
	}
	char* ret = zsys_getcwd(buf, size);
	if (!ret)
		return 0;
        ZASSERT(ret == buf);
	if (!buf[0] || buf[0] != '/') {
		errno = ENOENT;
		return 0;
	}
	return buf == tmp ? strdup(buf) : buf;
}
