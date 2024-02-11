#include <stdlib.h>
#include <stddef.h>
#include <netdb.h>
#include "lookup.h"
#include "lock.h"
#include <stdfil.h>

void freeaddrinfo(struct addrinfo *p)
{
    while (p) {
        struct addrinfo* next = p->ai_next;
        zfree(p->ai_addr);
        zfree(p->ai_canonname);
        zfree(p);
        p = next;
    }
}
