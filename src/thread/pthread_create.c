#define _GNU_SOURCE
#include "pthread_impl.h"
#include "stdio_impl.h"
#include "libc.h"
#include "lock.h"
#include <sys/mman.h>
#include <string.h>
#include <stddef.h>

static void dummy_0()
{
}
weak_alias(dummy_0, __acquire_ptc);
weak_alias(dummy_0, __release_ptc);
weak_alias(dummy_0, __pthread_tsd_run_dtors);
weak_alias(dummy_0, __do_orphaned_stdio_locks);
weak_alias(dummy_0, __dl_thread_cleanup);
weak_alias(dummy_0, __membarrier_init);

_Noreturn void __pthread_exit(void *result)
{
    zerror("pthread_exit not implemented");
}

struct start_args {
	void *(*start_func)(void *);
	void *start_arg;
};

static void* start(void* p)
{
    struct start_args* args = p;
    set_new_internal_thread_data();
    void* (*start_func)(void*) = args->start_func;
    void* start_arg = args->start_arg;
    zfree(args);
    void* result = start_func(start_arg);

    internal_thread_data* data = get_internal_thread_data();
    size_t repeat;
    for (repeat = 4; repeat--;) {
        size_t index;
        _Bool found_something = 0;
        for (index = zlength(data->thread_locals); index--;) {
            unsigned long long old_version = thread_locals[index].version;
            if (old_version != data->thread_locals[index].version)
                continue;
            zfence();
            void* value = data->thread_locals[index].value;
            void (*destructor)(void* arg) = thread_locals[index].destructor;
            zfence();
            if (old_version != thread_locals[index].version || !value || !destructor)
                continue;
            data->thread_locals[index].value = NULL;
            destructor(value);
            found_something = 1;
        }
        if (!found_something)
            break;
    }

    destroy_internal_thread_data();
    
    return result;
}

int __pthread_create(pthread_t *restrict res, const pthread_attr_t *restrict attrp, void *(*entry)(void *), void *restrict arg)
{
    ZASSERT(!attrp);
    struct start_args* args = zalloc(struct start_args, 1);
    args->start_func = entry;
    args->start_arg = arg;
    void* thread = zthread_create(start, args);
    if (!thread) {
        zfree(args);
        return errno;
    }
    *res = thread;
    return 0;
}

weak_alias(__pthread_exit, pthread_exit);
weak_alias(__pthread_create, pthread_create);
