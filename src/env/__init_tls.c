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

static void* internal_thread_data_key;

static void internal_thread_data_destructor(void* data)
{
    zfree(data);
}

hidden void __init_tls(void)
{
    internal_thread_data_key = zthread_key_create(internal_thread_data_destructor);
    ZASSERT(internal_thread_data_key);
    set_new_internal_thread_data();
}

hidden internal_thread_data* get_internal_thread_data(void)
{
    ZASSERT(internal_thread_data_key);
    return (internal_thread_data*)zthread_getspecific(internal_thread_data_key);
}

hidden void set_new_internal_thread_data(void)
{
    ZASSERT(!get_internal_thread_data());
    internal_thread_data* data = zalloc(internal_thread_data, 1);
    data->the_errno = 0;
    data->locale = &libc.global_locale;
    ZASSERT(zthread_setspecific(internal_thread_data_key, data));
}

