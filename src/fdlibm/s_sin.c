/* @(#)s_sin.c 1.3 95/01/18 */
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

/* sin(x)
 * Return sine function of x.
 *
 * kernel function:
 *	__kernel_sin		... sine function on [-pi/4,pi/4]
 *	__kernel_cos		... cose function on [-pi/4,pi/4]
 *	__ieee754_rem_pio2	... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on 
 *	[-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2 
 *	in [-pi/4 , +pi/4], and let n = k mod 4.
 *	We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *	    0	       S	   C		 T
 *	    1	       C	  -S		-1/T
 *	    2	      -S	  -C		 T
 *	    3	      -C	   S		-1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *	TRIG(x) returns trig(x) nearly rounded 
 */

#include "fdlibm.h"

#ifdef __STDC__
void sin(double x, double* result)
#else
void sin(x, result)
        double x; double* result;
#endif
{
    double y[2], z = 0.0;
    int n, ix;

    /* High word of x. */
    ix = __HI(x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if (ix <= 0x3fe921fb) {
        __kernel_sin(x, z, 0, result);
        return;

        /* sin(Inf or NaN) is NaN */
    }
    else if (ix >= 0x7ff00000) {
        *result = x - x;
        return;

        /* argument reduction needed */
    }
    else {
        n = __ieee754_rem_pio2(x, y);
        switch (n & 3) {
            case 0:
                __kernel_sin(y[0], y[1], 1, result);
                return;
            case 1:
                __kernel_cos(y[0], y[1], result);
                return;
            case 2:
                __kernel_sin(y[0], y[1], 1, result);
                *result = -*result;
                return;
            default:
                __kernel_cos(y[0], y[1], result);
                *result = -*result;
                return;
        }
    }
}
