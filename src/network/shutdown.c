#include <sys/socket.h>
#include "syscall.h"

int shutdown(int fd, int how)
{
    return zsys_shutdown(fd, how);
}
