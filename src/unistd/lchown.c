#include <unistd.h>
#include <fcntl.h>
#include "syscall.h"

int lchown(const char *path, uid_t uid, gid_t gid)
{
    return zsys_lchown(path, uid, gid);
}
