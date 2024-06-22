#include <setjmp.h>
#include <stdfil.h>

_Noreturn void longjmp(jmp_buf buf, int value)
{
    zlongjmp((zjmp_buf*)buf[0].__p, value);
}

_Noreturn void _longjmp(jmp_buf buf, int value)
{
    z_longjmp((zjmp_buf*)buf[0].__p, value);
}

_Noreturn void siglongjmp(sigjmp_buf buf, int value)
{
    zsiglongjmp((zjmp_buf*)buf[0].__p, value);
}
