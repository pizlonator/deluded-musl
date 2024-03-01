#include <dirent.h>
#include <errno.h>
#include <stddef.h>
#include "__dirent.h"
#include "syscall.h"
#include <stdfil.h>

struct dirent *readdir(DIR *dir)
{
    return (struct dirent*)zsys_readdir(dir);
}
