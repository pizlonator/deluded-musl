#define _DIRENT_HAVE_D_RECLEN
#define _DIRENT_HAVE_D_OFF
#define _DIRENT_HAVE_D_TYPE

struct dirent {
	ino_t d_ino;
	unsigned short d_reclen;
	unsigned char d_type;
	char d_name[256];
};
