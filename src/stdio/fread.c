#include "stdio_impl.h"
#include <string.h>
#include <stdfil.h>

#define MIN(a,b) ((a)<(b) ? (a) : (b))

size_t fread(void *restrict destv, size_t size, size_t nmemb, FILE *restrict f)
{
	unsigned char *dest = destv;
	size_t len = size*nmemb, l = len, k;
	if (!size) nmemb = 0;

	FLOCK(f);

	f->mode |= f->mode-1;

	if (f->rpos != f->rend) {
		/* First exhaust the buffer. */
		k = MIN(f->rend - f->rpos, l);
		memcpy(dest, f->rpos, k);
		f->rpos += k;
		dest += k;
		l -= k;
	}
	
	/* Read the remainder directly */
	for (; l; l-=k, dest+=k) {
		k = __toread(f) ? 0 : f->read(f, dest, l);
		if (!k) {
			FUNLOCK(f);
			return (len-l)/size;
		}
	}

	FUNLOCK(f);
	return nmemb;
}

weak_alias(fread, fread_unlocked);

size_t fread_znullify(void* dest, size_t size, size_t nmemb, FILE* f)
{
	void* tmp_buf = zgc_alloc(size * nmemb);
	size_t result = fread(tmp_buf, size, nmemb, f);
	zmemmove_nullify(dest, tmp_buf, result * size);
	zgc_free(tmp_buf);
	return result;
}
