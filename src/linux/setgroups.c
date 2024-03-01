#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include "syscall.h"
#include "libc.h"
#include <stdfil.h>

int setgroups(size_t count, const gid_t list[])
{
    return zsys_setgroups(count, list);
}
