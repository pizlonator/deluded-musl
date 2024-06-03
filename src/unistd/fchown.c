#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "syscall.h"

int fchown(int fd, uid_t uid, gid_t gid)
{
    return zsys_fchown(fd, uid, gid);
}
