#include <sys/socket.h>
#include "syscall.h"
#include <stdfil.h>

int bind(int fd, const struct sockaddr *addr, socklen_t len)
{
    return zsys_bind(fd, addr, len);
}
