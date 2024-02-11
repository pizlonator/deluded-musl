#include <sys/socket.h>
#include "syscall.h"
#include <stdfil.h>

int connect(int fd, const struct sockaddr *addr, socklen_t len)
{
    return zsys_connect(fd, addr, len);
}
