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
        zgc_free(p->ai_addr);
        zgc_free(p->ai_canonname);
        zgc_free(p);
        p = next;
    }
}
