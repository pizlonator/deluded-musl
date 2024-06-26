#include <dirent.h>
#include <unistd.h>
#include "__dirent.h"
#include "lock.h"
#include <pizlonated_musl_syscalls.h>

void seekdir(DIR *dir, long off)
{
    return zsys_seekdir(dir, off);
}
