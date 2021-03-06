/* @(#)s_rint.c 1.3 95/01/18 */
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
 * rint(x)
 * Return x rounded to integral value according to the prevailing
 * rounding mode.
 * Method:
 *	Using floating addition.
 * Exception:
 *	Inexact flag raised if x not equal to rint(x).
 */

#include "fdlibm.h"

#ifdef __STDC__
static const double
#else
static double
#endif
        TWO52[2] = {
        4.50359962737049600000e+15, /* 0x43300000, 0x00000000 */
        -4.50359962737049600000e+15, /* 0xC3300000, 0x00000000 */
};

#ifdef __STDC__
void rint(double x, double* result)
#else
void rint(x, result)
        double x; double* result;
#endif
{
    int i0, j0, sx;
    unsigned i, i1;
    double w, t;
    i0 = __HI(x);
    sx = (i0 >> 31) & 1;
    i1 = __LO(x);
    j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
    if (j0 < 20) {
        if (j0 < 0) {
            if (((i0 & 0x7fffffff) | i1) == 0) {
                *result = x;
                return;
            }
            i1 |= (i0 & 0x0fffff);
            i0 &= 0xfffe0000;
            i0 |= ((i1 | -i1) >> 12) & 0x80000;
            __HI(x) = i0;
            w = TWO52[sx] + x;
            t = w - TWO52[sx];
            i0 = __HI(t);
            __HI(t) = (i0 & 0x7fffffff) | (sx << 31);
            *result = t;
            return;
        }
        else {
            i = (0x000fffff) >> j0;
            if (((i0 & i) | i1) == 0) {
                *result = x; /* x is integral */
                return;
            }
            i >>= 1;
            if (((i0 & i) | i1) != 0) {
                if (j0 == 19) {
                    i1 = 0x40000000;
                }
                else {
                    i0 = (i0 & (~i)) | ((0x20000) >> j0);
                }
            }
        }
    }
    else if (j0 > 51) {
        if (j0 == 0x400) {
            *result = x + x;    /* inf or NaN */
        }
        else {
            *result = x;        /* x is integral */
        }
        return;
    }
    else {
        i = ((unsigned) (0xffffffff)) >> (j0 - 20);
        if ((i1 & i) == 0) {
            *result = x;    /* x is integral */
            return;
        }
        i >>= 1;
        if ((i1 & i) != 0) {
            i1 = (i1 & (~i)) | ((0x40000000) >> (j0 - 20));
        }
    }
    __HI(x) = i0;
    __LO(x) = i1;
    w = TWO52[sx] + x;
    *result = w - TWO52[sx];
    return;
}
