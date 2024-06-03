#include <sys/stat.h>
#include <stdfil.h>

int futimens(int fd, const struct timespec times[2])
{
    return zsys_futimens(fd, times);
}
