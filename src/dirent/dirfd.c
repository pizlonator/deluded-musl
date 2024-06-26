#include <dirent.h>
#include "__dirent.h"
#include <pizlonated_musl_syscalls.h>

int dirfd(DIR *d)
{
    return zsys_dirfd(d);
}
