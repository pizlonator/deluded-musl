#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <stdfil.h>

int socket(int domain, int type, int protocol)
{
    int s = zsys_socket(domain, type & ~(SOCK_CLOEXEC | SOCK_NONBLOCK), protocol);
    if (s < 0)
        return -1;
    if (type & SOCK_CLOEXEC)
        zsys_fcntl(s, F_SETFD, FD_CLOEXEC);
    if (type & SOCK_NONBLOCK)
        zsys_fcntl(s, F_SETFL, O_NONBLOCK);
    return s;
}
