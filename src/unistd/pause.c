#include <unistd.h>
#include "syscall.h"
#include <stdfil.h>

int pause(void)
{
    return zsys_pause();
}
