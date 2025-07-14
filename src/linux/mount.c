#include <sys/mount.h>
#include "syscall.h"

int mount(const char *special, const char *dir, const char *fstype, unsigned long flags, const void *data)
{
        return zsys_mount(special, dir, fstype, flags, data);
}

int umount(const char *special)
{
        return zsys_umount2(special, 0);
}

int umount2(const char *special, int flags)
{
        return zsys_umount2(special, flags);
}
