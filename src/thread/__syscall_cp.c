#include "pthread_impl.h"
#include "syscall.h"
#include <stdfil.h>

long (__syscall_cp)(syscall_arg_t nr,
                    syscall_arg_t u, syscall_arg_t v, syscall_arg_t w,
                    syscall_arg_t x, syscall_arg_t y, syscall_arg_t z)
{
    zerror("Don't do syscalls like this");
    return 0;
}
