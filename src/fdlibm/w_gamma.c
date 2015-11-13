/* @(#)w_gamma.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 *
 */

/* double gamma(double x)
 * Return the logarithm of the Gamma function of x.
 *
 * Method: call gamma_r
 */

#include "fdlibm.h"

extern int signgam;

#ifdef __STDC__
void gamma(double x, double* result)
#else
void gamma(x, result)
        double x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_gamma_r(x,&signgam, result);
    return;
#else
    double y;
    __ieee754_gamma_r(x, &signgam, &y);
    if (_LIB_VERSION == _IEEE_) {
        *result = y;
        return;
    }
    if (!finite(y) && finite(x)) {
        double floorX;
        floor(x, &floorX);

        if (floorX == x && x <= 0.0) {
            __kernel_standard(x, x, 41, result); /* gamma pole */
            return;
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
