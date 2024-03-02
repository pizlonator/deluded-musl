#define _GNU_SOURCE
#include <grp.h>
#include <limits.h>
#include <stdfil.h>

int initgroups(const char *user, gid_t gid)
{
    return zsys_initgroups(user, gid);
}
