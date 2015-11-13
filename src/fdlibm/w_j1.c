/* @(#)w_j1.c 1.3 95/01/18 */
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
 * wrapper of j1,y1 
 */

#include "fdlibm.h"

#ifdef __STDC__
void j1(double x, double* result)		/* wrapper j1 */
#else
void j1(x, result)            /* wrapper j1 */
        double x;double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_j1(x, result);
    return;
#else
    double z;
    __ieee754_j1(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    double fabsV;
    fabs(x, &fabsV);

    if (fabsV > X_TLOSS) {
        __kernel_standard(x, x, 36, result); /* j1(|x|>X_TLOSS) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}

#ifdef __STDC__
void y1(double x, double* result)		/* wrapper y1 */
#else
void y1(x,result)            /* wrapper y1 */
        double x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_y1(x, result);
    return;
#else
    double z;
    __ieee754_y1(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    if (x <= 0.0) {
        if (x == 0.0) {
            /* d= -one/(x-x); */
            __kernel_standard(x, x, 10, result);
            return;
        }
        else {
            /* d = zero/(x-x); */
            __kernel_standard(x, x, 11, result);
            return;
        }
    }
    if (x > X_TLOSS) {
        __kernel_standard(x, x, 37, result); /* y1(x>X_TLOSS) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
