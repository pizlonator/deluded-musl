#include <sys/socket.h>
#include "syscall.h"
#include <stdfil.h>

ssize_t recvfrom(int fd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t *restrict alen)
{
    return zsys_recvfrom(fd, buf, len, flags, addr, alen);
}
