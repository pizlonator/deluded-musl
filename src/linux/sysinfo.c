#include <sys/sysinfo.h>
#include "syscall.h"

int __lsysinfo(struct sysinfo *info)
{
	return zsys_sysinfo(info);
}

weak_alias(__lsysinfo, sysinfo);
