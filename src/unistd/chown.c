#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int chown(const char *path, uid_t uid, gid_t gid)
{
    return zsys_chown(path, uid, gid);
}
