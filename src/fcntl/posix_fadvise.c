#include <fcntl.h>
#include "syscall.h"

int posix_fadvise(int fd, off_t base, off_t len, int advice)
{
    return 0;
}
