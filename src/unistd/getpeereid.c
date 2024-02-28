#include <unistd.h>
#include <stdfil.h>

int getpeereid(int fd, uid_t *uid, gid_t *gid) {
    return zsys_getpeereid(fd, uid, gid);
}

