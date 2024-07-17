#include <string.h>
#include <stdfil.h>

int memcmp(const void *vl, const void *vr, size_t n)
{
    return zmemcmp(vl, vr, n);
}
