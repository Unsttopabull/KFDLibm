/* @(#)w_j0.c 1.3 95/01/18 */
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
 * wrapper j0(double x), y0(double x)
 */

#include "fdlibm.h"

#ifdef __STDC__
void j0(double x, double* result)		/* wrapper j0 */
#else
void j0(x,result)            /* wrapper j0 */
        double x;double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_j0(x,result);
    return;
#else
    double z;
    __ieee754_j0(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    if (fabs(x) > X_TLOSS) {
        __kernel_standard(x, x, 34, result); /* j0(|x|>X_TLOSS) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}

#ifdef __STDC__
void y0(double x, double* result)		/* wrapper y0 */
#else
void y0(x, result)            /* wrapper y0 */
        double x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_y0(x, result);
    return;
#else
    double z;
    __ieee754_y0(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    if (x <= 0.0) {
        if (x == 0.0) {
            /* d= -one/(x-x); */
            __kernel_standard(x, x, 8, result);
        }
        else {
            /* d = zero/(x-x); */
            __kernel_standard(x, x, 9, result);
        }
    }
    if (x > X_TLOSS) {
        __kernel_standard(x, x, 35, result); /* y0(x>X_TLOSS) */
    }
    else {
        *result = z;
        return;
    }
#endif
}
