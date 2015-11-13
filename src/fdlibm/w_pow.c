/* @(#)w_pow.c 1.3 95/01/18 */
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
 * wrapper pow(x,y) return x**y
 */

#include "fdlibm.h"


#ifdef __STDC__
void pow(double x, double y, double* result)	/* wrapper pow */
#else
void pow(x, y, result)            /* wrapper pow */
        double x, y; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_pow(x,y, result);
    return;
#else
    __ieee754_pow(x, y, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(y)) {
        *result = z;
        return;
    }
    if (isnan(x)) {
        if (y == 0.0) {
            __kernel_standard(x, y, 42, result); /* pow(NaN,0.0) */
            return;
        }
        else {
            *result = z;
            return;
        }
    }
    if (x == 0.0) {
        if (y == 0.0) {
            __kernel_standard(x, y, 20, result);
            return;
        } /* pow(0.0,0.0) */
        if (finite(y) && y < 0.0) {
            __kernel_standard(x, y, 23, result);
            return;
        } /* pow(0.0,negative) */
        *result = z;
        return;
    }
    if (!finite(z)) {
        if (finite(x) && finite(y)) {
            if (isnan(z)) {
                __kernel_standard(x, y, 24, result); /* pow neg**non-int */
                return;
            }
            else {
                __kernel_standard(x, y, 21, result);
                return;
            } /* pow overflow */
        }
    }
    if (z == 0.0 && finite(x) && finite(y)) {
        __kernel_standard(x, y, 22, result);
        return;
    } /* pow underflow */
    *result = z;
    return;
#endif
}
