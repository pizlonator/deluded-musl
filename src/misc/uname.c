#include <sys/utsname.h>
#include "syscall.h"
#include <stdfil.h>

int uname(struct utsname *uts)
{
	return zsys_uname(uts);
}
