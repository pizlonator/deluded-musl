#define _GNU_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include "__dirent.h"
#include "syscall.h"
#include <stdfil.h>
#include <stdfil.h>

DIR *opendir(const char *name)
{
    return (DIR*)zsys_opendir(name);
}
