/* @(#)w_gamma_r.c 1.3 95/01/18 */
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
 * wrapper double gamma_r(double x, int *signgamp)
 */

#include "fdlibm.h"


#ifdef __STDC__
void gamma_r(double x, int *signgamp, double* result) /* wrapper lgamma_r */
#else
void gamma_r(x, signgamp, result)              /* wrapper lgamma_r */
        double x; int* signgamp;double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_gamma_r(x,signgamp, result);
    return;
#else
    double y;
    __ieee754_gamma_r(x, signgamp, &y);
    if (_LIB_VERSION == _IEEE_) {
        *result = y;
        return;
    }
    if (!finite(y) && finite(x)) {
        double floorX;
        floor(x, &floorX);
        if (floorX == x && x <= 0.0) {
            __kernel_standard(x, x, 41, result); /* gamma pole */
        }
        else {
            __kernel_standard(x, x, 40, result);
            return;
        } /* gamma overflow */
    }
    else {
        *result = y;
        return;
    }
#endif
}             
