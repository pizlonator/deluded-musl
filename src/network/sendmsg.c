#include <sys/socket.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "syscall.h"
#include <stdfil.h>

ssize_t sendmsg(int fd, const struct msghdr *msg, int flags)
{
    return zsys_sendmsg(fd, msg, flags);
}
