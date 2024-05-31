#include "stdio_impl.h"
#include <errno.h>
#include <unistd.h>

int pclose(FILE *f)
{
	int status, r;
	pid_t pid = f->pipe_pid;
	fclose(f);
    for (;;) {
        r = zsys_waitpid(pid, &status, 0);
        ZASSERT(r == pid || r == -1);
        if (r == pid)
            break;
        if (errno != EINTR)
            return -1;
    }
	return status;
}
