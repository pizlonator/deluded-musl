#include <poll.h>
#include <time.h>
#include <signal.h>
#include "syscall.h"
#include <stdfil.h>

int poll(struct pollfd *fds, nfds_t n, int timeout)
{
    return zsys_poll(fds, n, timeout);
}
