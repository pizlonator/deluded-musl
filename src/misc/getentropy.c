#define _BSD_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdfil.h>

int getentropy(void *buffer, size_t len)
{
    return zsys_getentropy(buffer, len);
}
