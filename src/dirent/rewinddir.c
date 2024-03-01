#include <dirent.h>
#include <unistd.h>
#include "__dirent.h"
#include "lock.h"
#include <stdfil.h>

void rewinddir(DIR *dir)
{
    zsys_rewinddir(dir);
}
