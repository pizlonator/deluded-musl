#include <dirent.h>
#include "__dirent.h"
#include <pizlonated_musl_syscalls.h>

long telldir(DIR *dir)
{
    return zsys_telldir(dir);
}
