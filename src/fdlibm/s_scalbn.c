/* @(#)s_scalbn.c 1.3 95/01/18 */
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
 * scalbn (double x, int n)
 * scalbn(x,n) returns x* 2**n  computed by  exponent  
 * manipulation rather than by actually performing an 
 * exponentiation or a multiplication.
 */

#include "fdlibm.h"

#ifdef __STDC__
static const double
#else
static double
#endif
        two54 = 1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
        twom54 = 5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
        huge = 1.0e+300,
        tiny = 1.0e-300;

#ifdef __STDC__
void scalbn (double x, int n, double* result)
#else
void scalbn(x, n, result)
        double x; int n; double* result;
#endif
{
    int k, hx, lx;
    hx = __HI(x);
    lx = __LO(x);
    k = (hx & 0x7ff00000) >> 20;        /* extract exponent */
    if (k == 0) {                /* 0 or subnormal x */
        if ((lx | (hx & 0x7fffffff)) == 0) {
            *result = x;
            return;
        } /* +-0 */
        x *= two54;
        hx = __HI(x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000) {
            *result = tiny * x;
            return;
        }    /*underflow*/
    }
    if (k == 0x7ff) {
        *result = x + x;
        return;
    }        /* NaN or Inf */
    k = k + n;
    if (k > 0x7fe) {
        double copysignV;
        copysign(huge, x, &copysignV);

        *result = huge * copysignV;
        return;
    } /* overflow  */
    if (k > 0)                /* normal result */
    {
        __HI(x) = (hx & 0x800fffff) | (k << 20);
        *result = x;
        return;
    }
    if (k <= -54) {
        if (n > 50000) {    /* in case integer overflow in n+k */
            double copysignV;
            copysign(huge, x, &copysignV);

            *result = huge * copysignV;    /*overflow*/
            return;
        }
        else {
            double copysignV;
            copysign(tiny, x, &copysignV);

            *result = tiny * copysignV;
            return;
        }
    }    /*underflow*/
    k += 54;                /* subnormal result */
    __HI(x) = (hx & 0x800fffff) | (k << 20);
    *result = x * twom54;
    return;
}
