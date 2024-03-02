#define _GNU_SOURCE
#include "pwf.h"
#include <grp.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <byteswap.h>
#include <errno.h>
#include "nscd.h"
#include <stdfil.h>

int getgrouplist(const char *user, gid_t gid, gid_t *groups, int *ngroups)
{
    return zsys_getgrouplist(user, gid, groups, ngroups);
}
