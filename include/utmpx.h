#ifndef _UTMPX_H
#define _UTMPX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define __NEED_pid_t
#define __NEED_uid_t
#define __NEED_time_t
#define __NEED_suseconds_t
#define __NEED_struct_timeval

#include <bits/alltypes.h>

struct utmpx {
	short ut_type;
	short __ut_pad1;
	pid_t ut_pid;
	char ut_line[32];
	char ut_id[4];
	char ut_user[32];
	char ut_host[256];
	struct {
		short __e_termination;
		short __e_exit;
	} ut_exit;
	int ut_session, __ut_pad2;
	struct timeval ut_tv;
	unsigned ut_addr_v6[4];
	char __unused[20];
};

struct lastlogx {
	struct timeval ll_tv;
	char ll_line[32];
	char ll_host[256];
};

void          endutxent(void);
struct utmpx *getutxent(void);
struct utmpx *getutxid(const struct utmpx *);
struct utmpx *getutxline(const struct utmpx *);
struct utmpx *pututxline(const struct utmpx *);
void          setutxent(void);

struct lastlogx *getlastlogx(uid_t, struct lastlogx *);
struct lastlogx *getlastlogxbyname(const char*, struct lastlogx *);

#if defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
#define e_exit __e_exit
#define e_termination __e_termination
void updwtmpx(const char *, const struct utmpx *);
int utmpxname(const char *);
#endif

#define EMPTY           0
#define RUN_LVL         1
#define BOOT_TIME       2
#define NEW_TIME        3
#define OLD_TIME        4
#define INIT_PROCESS    5
#define LOGIN_PROCESS   6
#define USER_PROCESS    7
#define DEAD_PROCESS    8

#ifdef __cplusplus
}
#endif

#endif
