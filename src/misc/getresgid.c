#define _GNU_SOURCE
#include <unistd.h>
#include "syscall.h"

int getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid)
{
	return zsys_getresgid(rgid, egid, sgid);
}
