#include <unistd.h>
#include "syscall.h"

void sync(void)
{
    zsys_sync();
}
