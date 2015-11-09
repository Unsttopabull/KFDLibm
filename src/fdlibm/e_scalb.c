/* @(#)e_scalb.c 1.3 95/01/18 */
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
 * __ieee754_scalb(x, fn) is provide for
 * passing various standard test suite. One 
 * should use scalbn() instead.
 */

#include "fdlibm.h"

#ifdef _SCALB_INT
#ifdef __STDC__
void __ieee754_scalb(double x, int fn, double* result)
#else
void __ieee754_scalb(x,fn,result)
double x; int fn; double* result;
#endif
#else
#ifdef __STDC__
void __ieee754_scalb(double x, double fn, double* result)
#else
void __ieee754_scalb(x,fn,result)
        double x, fn; double* result;
#endif
#endif
{
#ifdef _SCALB_INT
    scalbn(x,fn, result);
    return;
#else
    if (isnan(x) || isnan(fn)) {
        *result = x * fn;
        return;
    }
    if (!finite(fn)) {
        if (fn > 0.0) {
            *result = x * fn;
        }
        else {
            *result = x / (-fn);
        }
        return;
    }

    double rnt;
    rint(fn, &rnt);
    if (rnt != fn) {
        *result = (fn - fn) / (fn - fn);
        return;
    }
    if (fn > 65000.0) {
        scalbn(x, 65000, result);
        return;
    }
    if (-fn > 65000.0) {
        scalbn(x, -65000, result);
        return;
    }
    scalbn(x, (int) fn, result);
#endif
}
