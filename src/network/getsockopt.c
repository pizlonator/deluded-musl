#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include "syscall.h"
#include <stdfil.h>

int getsockopt(int fd, int level, int optname, void *restrict optval, socklen_t *restrict optlen)
{
    return zsys_getsockopt(fd, level, optname, optval, optlen);
}
