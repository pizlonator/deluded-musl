typedef unsigned int fexcept_t;

typedef struct {
	unsigned int __opaque[2];
} fenv_t;

#define FE_DFL_ENV      ((const fenv_t *) -1)
