#include <sys/socket.h>
#include "syscall.h"
#include <stdfil.h>

int accept(int fd, struct sockaddr *restrict addr, socklen_t *restrict len)
{
    return zsys_accept(fd, addr, len);
}
