#include <elf.h>
#include <link.h>
#include "pthread_impl.h"
#include "libc.h"
#include <stdfil.h>

static int static_dl_iterate_phdr(int(*callback)(struct dl_phdr_info *info, size_t size, void *data), void *data)
{
    zerror("static_dl_iterate_phdr not implemented");
}

weak_alias(static_dl_iterate_phdr, dl_iterate_phdr);
