#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "__dirent.h"
#include <stdfil.h>

int closedir(DIR *dir)
{
    return zsys_closedir(dir);
}
