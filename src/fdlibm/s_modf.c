/* @(#)s_modf.c 1.3 95/01/18 */
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
 * modf(double x, double *iptr) 
 * return fraction part of x, and return x's integral part in *iptr.
 * Method:
 *	Bit twiddling.
 *
 * Exception:
 *	No exception.
 */

#include "fdlibm.h"

#ifdef __STDC__
static const double one = 1.0;
#else
static double one = 1.0;
#endif

#ifdef __STDC__
void modf(double x, double *iptr, double* result)
#else
void modf(x, iptr, result)
        double x, * iptr; double* result;
#endif
{
    int i0, i1, j0;
    unsigned i;
    i0 = __HI(x);        /* high x */
    i1 = __LO(x);        /* low  x */
    j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;    /* exponent of x */
    if (j0 < 20) {            /* integer part in high x */
        if (j0 < 0) {            /* |x|<1 */
            __HIp(iptr) = i0 & 0x80000000;
            __LOp(iptr) = 0;        /* *iptr = +-0 */
            *result = x;
            return;
        }
        else {
            i = (0x000fffff) >> j0;
            if (((i0 & i) | i1) == 0) {        /* x is integral */
                *iptr = x;
                __HI(x) &= 0x80000000;
                __LO(x) = 0;    /* return +-0 */
                *result = x;
                return;
            }
            else {
                __HIp(iptr) = i0 & (~i);
                __LOp(iptr) = 0;
                *result = x - *iptr;
                return;
            }
        }
    }
    else if (j0 > 51) {        /* no fraction part */
        *iptr = x * one;
        __HI(x) &= 0x80000000;
        __LO(x) = 0;    /* return +-0 */
        *result = x;
        return;
    }
    else {            /* fraction part in low x */
        i = ((unsigned) (0xffffffff)) >> (j0 - 20);
        if ((i1 & i) == 0) {        /* x is integral */
            *iptr = x;
            __HI(x) &= 0x80000000;
            __LO(x) = 0;    /* return +-0 */
            *result = x;
            return;
        }
        else {
            __HIp(iptr) = i0;
            __LOp(iptr) = i1 & (~i);
            *result = x - *iptr;
            return;
        }
    }
}
