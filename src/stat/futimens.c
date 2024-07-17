#include <sys/stat.h>
#include <pizlonated_musl_syscalls.h>

int futimens(int fd, const struct timespec times[2])
{
    return zsys_futimens(fd, times);
}
