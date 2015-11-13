/* @(#)w_scalb.c 1.3 95/01/18 */
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
 * wrapper scalb(double x, double fn) is provide for
 * passing various standard test suite. One 
 * should use scalbn() instead.
 */

#include "fdlibm.h"

#include <errno.h>

#ifdef __STDC__
#ifdef _SCALB_INT
void scalb(double x, int fn, double* result)		/* wrapper scalb */
#else
void scalb(double x, double fn, double* result)	/* wrapper scalb */
#endif
#else
void scalb(x, fn, result)            /* wrapper scalb */
#ifdef _SCALB_INT
double x; int fn; double* result;
#else
        double x, fn; double* result;
#endif
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_scalb(x,fn, result);
    return;
#else
    double z;
    __ieee754_scalb(x, fn, &z);
    if (_LIB_VERSION == _IEEE_) {
        *result = z;
        return;
    }
    if (!(finite(z) || isnan(z)) && finite(x)) {
        __kernel_standard(x, (double) fn, 32, result); /* scalb overflow */
        return;
    }
    if (z == 0.0 && z != x) {
        __kernel_standard(x, (double) fn, 33, result); /* scalb underflow */
        return;
    }
#ifndef _SCALB_INT
    if (!finite(fn)) {
        errno = ERANGE;
    }
#endif
    *result = z;
#endif
}
