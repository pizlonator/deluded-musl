#include <sys/socket.h>
#include "syscall.h"
#include <stdfil.h>

int getpeername(int fd, struct sockaddr *restrict addr, socklen_t *restrict len)
{
    return zsys_getpeername(fd, addr, len);
}
