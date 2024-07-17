#include <sys/socket.h>
#include "syscall.h"
#include <stdfil.h>

int listen(int fd, int backlog)
{
    return zsys_listen(fd, backlog);
}
