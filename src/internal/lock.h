#ifndef LOCK_H
#define LOCK_H

hidden void __lock(volatile int *);
hidden int __trylock(volatile int *);
hidden void __unlock(volatile int *);
#define LOCK(x) __lock(x)
#define TRYLOCK(x) __trylock(x)
#define UNLOCK(x) __unlock(x)

#endif
