/* @(#)e_cosh.c 1.3 95/01/18 */
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

/* __ieee754_cosh(x)
 * Method : 
 * mathematically cosh(x) if defined to be (exp(x)+exp(-x))/2
 *	1. Replace x by |x| (cosh(x) = cosh(-x)). 
 *	2. 
 *		                                        [ exp(x) - 1 ]^2 
 *	    0        <= x <= ln2/2  :  cosh(x) := 1 + -------------------
 *			       			           2*exp(x)
 *
 *		                                  exp(x) +  1/exp(x)
 *	    ln2/2    <= x <= 22     :  cosh(x) := -------------------
 *			       			          2
 *	    22       <= x <= lnovft :  cosh(x) := exp(x)/2 
 *	    lnovft   <= x <= ln2ovft:  cosh(x) := exp(x/2)/2 * exp(x/2)
 *	    ln2ovft  <  x	    :  cosh(x) := huge*huge (overflow)
 *
 * Special cases:
 *	cosh(x) is |x| if x is +INF, -INF, or NaN.
 *	only cosh(0)=1 is exact for finite x.
 */

#include "fdlibm.h"

#ifdef __STDC__
static const double one = 1.0, half=0.5, huge = 1.0e300;
#else
static double one = 1.0, half = 0.5, huge = 1.0e300;
#endif

#ifdef __STDC__
void __ieee754_cosh(double x, double* result)
#else
void __ieee754_cosh(x, result)
        double x; double *result;
#endif
{
    double t, w;
    int ix;
    unsigned lx;

    /* High word of |x|. */
    ix = __HI(x);
    ix &= 0x7fffffff;

    /* x is INF or NaN */
    if (ix >= 0x7ff00000) {
        *result = x * x;
        return;
    }

    /* |x| in [0,0.5*ln2], return 1+expm1(|x|)^2/(2*exp(|x|)) */
    if (ix < 0x3fd62e43) {
        double fbs;
        fabs(x, &fbs);

        expm1(fbs, &t);
        w = one + t;
        if (ix < 0x3c800000) {
            *result = w;
            return;
        }    /* cosh(tiny) = 1 */
        *result = one + (t * t) / (w + w);
        return;
    }

    /* |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2; */
    if (ix < 0x40360000) {
        double fbs;
        fabs(x, &fbs);

        __ieee754_exp(fbs, &t);
        *result = half * t + half / t;
        return;
    }

    /* |x| in [22, log(maxdouble)] return half*exp(|x|) */
    if (ix < 0x40862E42) {
        double fbs;
        fabs(x, &fbs);

        double expv;
        __ieee754_exp(fbs, &expv);

        *result = half * expv;
        return;
    }

    /* |x| in [log(maxdouble), overflowthresold] */
    lx = *((((*(unsigned *) &one) >> 29)) + (unsigned *) &x);
    if (ix < 0x408633CE || (ix == 0x408633ce) && (lx <= (unsigned) 0x8fb9f87d)) {
        double fbs;
        fabs(x, &fbs);

        __ieee754_exp(half * fbs, &w);
        t = half * w;
        *result = t * w;
        return;
    }

    /* |x| > overflowthresold, cosh(x) overflow */
    *result = huge * huge;
    return;
}
