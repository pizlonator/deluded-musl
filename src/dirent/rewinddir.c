#include <dirent.h>
#include <unistd.h>
#include "__dirent.h"
#include "lock.h"
#include <pizlonated_musl_syscalls.h>

void rewinddir(DIR *dir)
{
    zsys_rewinddir(dir);
}
