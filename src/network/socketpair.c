#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include "syscall.h"
#include <stdfil.h>

int socketpair(int domain, int type, int protocol, int fd[2])
{
    return zsys_socketpair(domain, type, protocol, fd);
}
