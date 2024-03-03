#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pty.h>
#include <stdio.h>
#include <pthread.h>
#include <stdfil.h>

int openpty(int *pm, int *ps, char *name, const struct termios *tio, const struct winsize *ws)
{
    return zsys_openpty(pm, ps, name, tio, ws);
}
