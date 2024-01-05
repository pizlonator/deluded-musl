#include <setjmp.h>
#include <stdfil.h>

_Noreturn void longjmp(jmp_buf buf, int value)
{
    zerror("longjmp is disallowed");
}
