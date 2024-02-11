#include <sys/socket.h>
#include "syscall.h"
#include <stdfil.h>

int getsockname(int fd, struct sockaddr *restrict addr, socklen_t *restrict len)
{
    return zsys_getsockname(fd, addr, len);
}
