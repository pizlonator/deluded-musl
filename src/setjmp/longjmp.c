#include <setjmp.h>
#include <pizlonated_runtime.h>

_Noreturn void longjmp(jmp_buf buf, int value)
{
    zlongjmp(*(zjmp_buf**)buf, value);
}

_Noreturn void _longjmp(jmp_buf buf, int value)
{
    zlongjmp(*(zjmp_buf**)buf, value);
}

_Noreturn void siglongjmp(sigjmp_buf buf, int value)
{
    zlongjmp(*(zjmp_buf**)buf, value);
}
