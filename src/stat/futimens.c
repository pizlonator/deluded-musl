#include <sys/stat.h>
#include <pizlonated_syscalls.h>

int futimens(int fd, const struct timespec times[2])
{
    return zsys_futimens(fd, times);
}
