
/* @(#)fdlibm.h 1.5 04/04/22 */
/*
 * ====================================================
 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* Sometimes it's necessary to define __LITTLE_ENDIAN explicitly
   but these catch some common cases. */

#if defined(i386) || defined(i486) || \
	defined(intel) || defined(x86) || defined(i86pc) || \
	defined(__alpha) || defined(__osf__) || \
	defined(__i386) || defined(_X86_) || defined(__x86_64__)
#define __LITTLE_ENDIAN
#endif

#ifdef __LITTLE_ENDIAN
#define __HI(x) *(1+(int*)&x)
#define __LO(x) *(int*)&x
#define __HIp(x) *(1+(int*)x)
#define __LOp(x) *(int*)x
#else
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)
#define __HIp(x) *(int*)x
#define __LOp(x) *(1+(int*)x)
#endif

#ifdef __STDC__
#define	__P(p)	p
#else
#define	__P(p)	()
#endif

/*
 * ANSI/POSIX
 */

extern int signgam;

#define	MAXFLOAT	((float)3.40282346638528860e+38)

enum fdversion {fdlibm_ieee = -1, fdlibm_svid, fdlibm_xopen, fdlibm_posix};

#define _LIB_VERSION_TYPE enum fdversion
#define _LIB_VERSION _fdlib_version

/* if global variable _LIB_VERSION is not desirable, one may 
 * change the following to be a constant by: 
 *	#define _LIB_VERSION_TYPE const enum version
 * In that case, after one initializes the value _LIB_VERSION (see
 * s_lib_version.c) during compile time, it cannot be modified
 * in the middle of a program
 */
extern  _LIB_VERSION_TYPE  _LIB_VERSION;

#define _IEEE_  fdlibm_ieee
#define _SVID_  fdlibm_svid
#define _XOPEN_ fdlibm_xopen
#define _POSIX_ fdlibm_posix

struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

#define	HUGE		MAXFLOAT

/* 
 * set X_TLOSS = pi*2**52, which is possibly defined in <values.h>
 * (one may replace the following line by "#include <values.h>")
 */

#define X_TLOSS		1.41484755040568800000e+16

#define	DOMAIN		1
#define	SING		2
#define	OVERFLOW	3
#define	UNDERFLOW	4
#define	TLOSS		5
#define	PLOSS		6

/*
 * ANSI/POSIX
 */
extern void acos __P((double, double*));
extern void asin __P((double, double*));
extern void atan __P((double,double*));
extern void atan2 __P((double, double, double*));
extern void cos __P((double, double*));
extern void sin __P((double, double*));
extern void tan __P((double, double*));

extern void cosh __P((double, double*));
extern void sinh __P((double, double*));
extern void tanh __P((double, double*));

extern void exp __P((double,double*));
extern void frexp __P((double, int*, double*));
extern void ldexp __P((double, int, double*));
extern void log __P((double, double*));
extern void log10 __P((double, double*));
extern void modf __P((double, double*, double*));

extern void pow __P((double, double, double*));
extern void sqrt __P((double,double*));

extern void ceil __P((double, double*));
extern void fabs __P((double,double*));
extern void floor __P((double,double*));
extern void fmod __P((double, double, double*));

extern void erf __P((double, double*));
extern void erfc __P((double, double*));
extern void gamma __P((double, double*));
extern void hypot __P((double, double, double*));
extern int isnan __P((double));
extern int finite __P((double));
extern void j0 __P((double, double*));
extern void j1 __P((double, double*));
extern void jn __P((int, double, double*));
extern void lgamma __P((double, double*));
extern void y0 __P((double, double*));
extern void y1 __P((double, double*));
extern void yn __P((int, double, double*));

extern void acosh __P((double, double*));
extern void asinh __P((double, double*));
extern void atanh __P((double, double*));
extern void cbrt __P((double, double*));
extern void logb __P((double, double*));
extern void nextafter __P((double, double, double*));
extern void remainder __P((double, double, double*));
#ifdef _SCALB_INT
extern void scalb __P((double, int, double*));
#else
extern void scalb __P((double, double, double*));
#endif

extern int matherr __P((struct exception *));

/*
 * IEEE Test Vector
 */
extern void significand __P((double,double*));

/*
 * Functions callable from C, intended to support IEEE arithmetic.
 */
extern void copysign __P((double, double, double*));
extern int ilogb __P((double));
extern void rint __P((double, double *));
extern void scalbn __P((double, int, double*));

/*
 * BSD math library entry points
 */
extern void expm1 __P((double, double*));
extern void log1p __P((double,double*));

/*
 * Reentrant version of gamma & lgamma; passes signgam back by reference
 * as the second argument; user must allocate space for signgam.
 */
#ifdef _REENTRANT
extern double gamma_r __P((double, int *));
extern double lgamma_r __P((double, int *));
#endif	/* _REENTRANT */

/* ieee style elementary functions */
extern void __ieee754_sqrt __P((double, double*));
extern void __ieee754_acos __P((double, double*));
extern void __ieee754_acosh __P((double,double*));
extern void __ieee754_log __P((double,double*));
extern void __ieee754_atanh __P((double,double*));
extern void __ieee754_asin __P((double,double*));
extern void __ieee754_atan2 __P((double,double,double*));
extern void __ieee754_exp __P((double, double*));
extern void __ieee754_cosh __P((double,double*));
extern void __ieee754_fmod __P((double,double, double*));
extern void __ieee754_pow __P((double,double,double*));
extern void __ieee754_lgamma_r __P((double,int *, double*));
extern void __ieee754_gamma_r __P((double,int *, double*));
extern void __ieee754_lgamma __P((double, double*));
extern void __ieee754_gamma __P((double, double*));
extern void __ieee754_log10 __P((double, double*));
extern void __ieee754_sinh __P((double, double*));
extern void __ieee754_hypot __P((double,double,double*));
extern void __ieee754_j0 __P((double,double*));
extern void __ieee754_j1 __P((double, double*));
extern void __ieee754_y0 __P((double,double*));
extern void __ieee754_y1 __P((double, double*));
extern void __ieee754_jn __P((int,double,double*));
extern void __ieee754_yn __P((int,double,double*));
extern void __ieee754_remainder __P((double,double, double*));
extern int    __ieee754_rem_pio2 __P((double,double*));
#ifdef _SCALB_INT
extern void __ieee754_scalb __P((double,int,double*));
#else
extern void __ieee754_scalb __P((double,double,double*));
#endif

//#pragma GCC visibility push(hidden)
/* fdlibm kernel function */
extern void __kernel_standard __P((double,double,int,double*));
extern void __kernel_sin __P((double,double,int,double*));
extern void __kernel_cos __P((double,double,double*));
extern void __kernel_tan __P((double,double,int,double*));
extern int    __kernel_rem_pio2 __P((double*,double*,int,int,int,const int*));
//#pragma GCC visibility pop
