#include <setjmp.h>
#include <stdfil.h>

int setjmp(jmp_buf buf)
{
    zerror("setjmp is disallowed");
    return 0;
}
