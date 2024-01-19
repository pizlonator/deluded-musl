#include <errno.h>
#include "pthread_impl.h"

int *__errno_location(void)
{
    return &get_internal_thread_data()->the_errno;
}

weak_alias(__errno_location, ___errno_location);
