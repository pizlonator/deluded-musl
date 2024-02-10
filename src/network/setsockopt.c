#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include "syscall.h"
#include <stdfil.h>

int setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
    return zsys_setsockopt(fd, level, optname, optval, optlen);
}
