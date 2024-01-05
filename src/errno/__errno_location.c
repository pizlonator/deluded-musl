#include <errno.h>
#include "pthread_impl.h"

// FIXME: We'll have to fix this when we support threads!!!!!
static int global_errno_hack;

int *__errno_location(void)
{
	return &global_errno_hack;
}

weak_alias(__errno_location, ___errno_location);
