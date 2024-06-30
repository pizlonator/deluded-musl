#include <sys/mman.h>
#include "libc.h"
#include "syscall.h"

int __mprotect(void *addr, size_t len, int prot)
{
    return zsys_mprotect(addr, len, prot);
}

weak_alias(__mprotect, mprotect);
