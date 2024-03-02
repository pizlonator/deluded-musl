#define _GNU_SOURCE 1
#include <stdarg.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include "lock.h"
#include "fork_impl.h"
#include <stdfil.h>
#include <stdio.h>
#include <stdlib.h>

static volatile int lock[1];
static char log_ident[32];
static int log_opt;
static int log_facility = LOG_USER;
static int log_mask = 0xff;
static int log_fd = -1;
volatile int *const __syslog_lockptr = lock;

int setlogmask(int maskpri)
{
    return zsys_setlogmask(maskpri);
}

void closelog(void)
{
    zsys_closelog();
}

void openlog(const char *ident, int opt, int facility)
{
    zsys_openlog(ident, opt, facility);
}

static void __vsyslog(int priority, const char *message, va_list ap)
{
    char* str;
    vasprintf(&str, message, ap);
    zsys_syslog(priority, str);
    free(str);
}

void syslog(int priority, const char *message, ...)
{
	va_list ap;
	va_start(ap, message);
	__vsyslog(priority, message, ap);
	va_end(ap);
}

weak_alias(__vsyslog, vsyslog);
