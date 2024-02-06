#define _GNU_SOURCE
#include <unistd.h>
#include "pthread_impl.h"

pid_t gettid(void)
{
    zerror("gettid not implemented because tids aren't pids and Linux got it wrong");
    return 0;
}
