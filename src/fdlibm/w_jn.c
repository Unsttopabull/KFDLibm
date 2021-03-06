/* @(#)w_jn.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/*
 * wrapper jn(int n, double x), yn(int n, double x)
 * floating point Bessel's function of the 1st and 2nd kind
 * of order n
 *          
 * Special cases:
 *	y0(0)=y1(0)=yn(n,0) = -inf with division by zero signal;
 *	y0(-ve)=y1(-ve)=yn(n,-ve) are NaN with invalid signal.
 * Note 2. About jn(n,x), yn(n,x)
 *	For n=0, j0(x) is called,
 *	for n=1, j1(x) is called,
 *	for n<x, forward recursion us used starting
 *	from values of j0(x) and j1(x).
 *	for n>x, a continued fraction approximation to
 *	j(n,x)/j(n-1,x) is evaluated and then backward
 *	recursion is used starting from a supposed value
 *	for j(n,x). The resulting value of j(0,x) is
 *	compared with the actual value to correct the
 *	supposed value of j(n,x).
 *
 *	yn(n,x) is similar in all respects, except
 *	that forward recursion is used for all
 *	values of n>1.
 *	
 */

#include "fdlibm.h"

#ifdef __STDC__
void jn(int n, double x, double* result)	/* wrapper jn */
#else
void jn(n, x, result)            /* wrapper jn */
        double x; int n; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_jn(n,x,result);
    return;
#else
    double z;
    __ieee754_jn(n, x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    double fabsV;
    fabs(x, &fabsV);

    if (fabsV > X_TLOSS) {
        __kernel_standard((double) n, x, 38, result); /* jn(|x|>X_TLOSS,n) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}

#ifdef __STDC__
void yn(int n, double x, double* result)	/* wrapper yn */
#else
void yn(n, x, result)            /* wrapper yn */
        double x; int n; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_yn(n,x,result);
    return;
#else
    double z;
    __ieee754_yn(n, x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    if (x <= 0.0) {
        if (x == 0.0) {
            /* d= -one/(x-x); */
            __kernel_standard((double) n, x, 12, result);
            return;
        }
        else {
            /* d = zero/(x-x); */
            __kernel_standard((double) n, x, 13, result);
            return;
        }
    }
    if (x > X_TLOSS) {
        __kernel_standard((double) n, x, 39, result); /* yn(x>X_TLOSS,n) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
