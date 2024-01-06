#include "stdio_impl.h"
#include "aio_impl.h"
#include <stdfil.h>

static int dummy(int fd)
{
	return fd;
}

weak_alias(dummy, __aio_close);

int __stdio_close(FILE *f)
{
	return zsys_close(__aio_close(f->fd));
}
