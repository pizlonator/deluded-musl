#ifndef LIBC_H
#define LIBC_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdfil.h>
#include <pizlonated_musl_syscalls.h>

struct __locale_map;

struct __locale_struct {
	const struct __locale_map *cat[6];
};

struct tls_module {
	struct tls_module *next;
	void *image;
	size_t len, size, align, offset;
};

struct __libc {
	char secure;
	size_t *auxv;
	struct tls_module *tls_head;
	size_t tls_size, tls_align, tls_cnt;
	size_t page_size;
	struct __locale_struct global_locale;
};

#ifndef PAGE_SIZE
#define PAGE_SIZE libc.page_size
#endif

extern hidden struct __libc __libc;
#define libc __libc

void __init_libc(char **, char *);
hidden void __init_tls(void);
hidden void __init_ssp(void *);
hidden void __libc_start_init(void);
hidden void __funcs_on_exit(void);
hidden void __funcs_on_quick_exit(void);
hidden void __libc_exit_fini(void);
hidden void __fork_handler(int);

extern hidden size_t __hwcap;
extern hidden size_t __sysinfo;
extern char *__progname, *__progname_full;

extern hidden const char __libc_version[];

#define __synccall(callback, arg) zerrorf("%s:%d: %s: attempt to __synccall(%s, %s)", __FILE__, __LINE__, __PRETTY_FUNCTION__, #callback, #arg)
hidden int __setxid(int, int, int, int);

#endif
