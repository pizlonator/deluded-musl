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

char *dlerror()
{
    internal_thread_data* data = get_internal_thread_data();
    if (!data->dlerror_flag)
        return NULL;

    data->dlerror_flag = 0;
    return data->dlerror_string;
}

hidden void __dl_vseterr(const char *fmt, va_list ap)
{
	va_list ap2;
	va_copy(ap2, ap);
        internal_thread_data* data = get_internal_thread_data();
        if (data->dlerror_string)
            zfree(data->dlerror_string);
	size_t len = vsnprintf(0, 0, fmt, ap2);
	if (len < sizeof(void *)) len = sizeof(void *);
	va_end(ap2);
	char *buf = (char*)zalloc(len+1);
        ZASSERT(buf);
        vsnprintf(buf, len+1, fmt, ap);
        data->dlerror_string = buf;
        data->dlerror_flag = 1;
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
