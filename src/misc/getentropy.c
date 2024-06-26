#define _BSD_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <pizlonated_musl_syscalls.h>

int getentropy(void *buffer, size_t len)
{
    return zsys_getentropy(buffer, len);
}
