#ifndef _FENV_H
#define _FENV_H

#ifdef __cplusplus
extern "C" {
#endif

#define FE_INVALID    1
#define FE_DIVBYZERO  2
#define FE_OVERFLOW   4
#define FE_UNDERFLOW  8
#define FE_INEXACT    16
#define FE_ALL_EXCEPT 31
#define FE_TONEAREST  0
#define FE_DOWNWARD   32
#define FE_UPWARD     64
#define FE_TOWARDZERO 96

#include <bits/fenv.h>

int feclearexcept(int);
int fegetexceptflag(fexcept_t *, int);
int feraiseexcept(int);
int fesetexceptflag(const fexcept_t *, int);
int fetestexcept(int);

int fegetround(void);
int fesetround(int);

int fegetenv(fenv_t *);
int feholdexcept(fenv_t *);
int fesetenv(const fenv_t *);
int feupdateenv(const fenv_t *);

#ifdef __cplusplus
}
#endif
#endif

