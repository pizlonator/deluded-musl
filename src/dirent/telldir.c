#include <dirent.h>
#include "__dirent.h"
#include <stdfil.h>

long telldir(DIR *dir)
{
    return zsys_telldir(dir);
}
