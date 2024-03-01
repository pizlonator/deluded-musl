#include <dirent.h>
#include "__dirent.h"
#include <stdfil.h>

int dirfd(DIR *d)
{
    return zsys_dirfd(d);
}
