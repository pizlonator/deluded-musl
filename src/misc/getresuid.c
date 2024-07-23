#define _GNU_SOURCE
#include <unistd.h>
#include "syscall.h"

int getresuid(uid_t *ruid, uid_t *euid, uid_t *suid)
{
	return zsys_getresuid(ruid, euid, suid);
}
