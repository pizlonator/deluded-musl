#define SYSCALL_NO_TLS 1
#include <elf.h>
#include <limits.h>
#include <sys/mman.h>
#include <string.h>
#include <stddef.h>
#include "pthread_impl.h"
#include "libc.h"
#include "atomic.h"
#include "syscall.h"
#include <stdfil.h>

volatile int __thread_list_lock;

hidden void destroy_internal_thread_data()
{
    internal_thread_data* data = get_internal_thread_data();
    zfree(data->dlerror_string);
    zfree(data);
}

hidden void __init_tls(void)
{
    set_new_internal_thread_data();
}

hidden internal_thread_data* get_internal_thread_data(void)
{
    internal_thread_data* result = (internal_thread_data*)zthread_self_cookie();
    ZASSERT(result);
    return result;
}

hidden void set_new_internal_thread_data(void)
{
    ZASSERT(!zthread_self_cookie());
    internal_thread_data* data = (internal_thread_data*)zalloc(sizeof(internal_thread_data));
    data->the_errno = 0;
    data->locale = &libc.global_locale;
    data->thread_locals = NULL;
    zthread_set_self_cookie(data);
}

