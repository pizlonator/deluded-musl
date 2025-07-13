#include <sys/reboot.h>
#include "syscall.h"

int reboot(int type)
{
	return zsys_reboot(type);
}
