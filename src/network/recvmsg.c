#include <sys/socket.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "syscall.h"
#include <stdfil.h>

ssize_t recvmsg(int fd, struct msghdr *msg, int flags)
{
    return zsys_recvmsg(fd, msg, flags);
}
