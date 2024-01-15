#include <dlfcn.h>
#include <stdlib.h>
#include <stdarg.h>
#include "pthread_impl.h"
#include "dynlink.h"
#include "atomic.h"
#include <stdfil.h>

#define malloc __libc_malloc
#define calloc __libc_calloc
#define realloc __libc_realloc
#define free __libc_free

typedef struct {
    char* string;
    int flag;
} dlerror_entry;

static void* dlerror_key;

static void error_destructor(void* entry_ptr)
{
    dlerror_entry* entry = (dlerror_entry*)entry_ptr;
    if (!entry)
        return;
    zfree(entry->string);
    zfree(entry);
}

hidden void __dl_initerror(void)
{
    dlerror_key = zthread_key_create(error_destructor);
    ZASSERT(dlerror_key);
}

char *dlerror()
{
    dlerror_entry* entry = (dlerror_entry*)zthread_getspecific(dlerror_key);
    if (!entry)
        return NULL;
    if (!entry->flag)
        return NULL;

    entry->flag = 0;
    return entry->string;
}

hidden void __dl_vseterr(const char *fmt, va_list ap)
{
	va_list ap2;
	va_copy(ap2, ap);
        dlerror_entry* entry = zthread_getspecific(dlerror_key);
        if (!entry) {
            entry = zalloc_zero(dlerror_entry, 1);
            zthread_setspecific(dlerror_key, entry);
        }
        if (entry->string)
            zfree(entry->string);
	size_t len = vsnprintf(0, 0, fmt, ap2);
	if (len < sizeof(void *)) len = sizeof(void *);
	va_end(ap2);
	char *buf = zalloc(char, len+1);
        ZASSERT(buf);
        vsnprintf(buf, len+1, fmt, ap);
        entry->string = buf;
        entry->flag = 1;
}

hidden void __dl_seterr(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	__dl_vseterr(fmt, ap);
	va_end(ap);
}

static int stub_invalid_handle(void *h)
{
	__dl_seterr("Invalid library handle %p", (void *)h);
	return 1;
}

weak_alias(stub_invalid_handle, __dl_invalid_handle);
