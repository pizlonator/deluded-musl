#include "pthread_impl.h"

int libc_internal_signals[] = {
    SIGTIMER,
    SIGCANCEL,
    SIGSYNCCALL
};

unsigned num_libc_internal_signals = 3;
