#include "pthread_impl.h"

void* pthread_getstack_yolo(pthread_t t)
{
    return t->stack;
}

size_t pthread_getstacksize_yolo(pthread_t t)
{
    return t->stack_size;
}

