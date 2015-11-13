/* @(#)s_logb.c 1.3 95/01/18 */
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
 * double logb(x)
 * IEEE 754 logb. Included to pass IEEE test suite. Not recommend.
 * Use ilogb instead.
 */

#include "fdlibm.h"

#ifdef __STDC__
void logb(double x, double* result)
#else
void logb(x, result)
        double x; double* result;
#endif
{
    int lx, ix;
    ix = (__HI(x)) & 0x7fffffff;    /* high |x| */
    lx = __LO(x);            /* low x */
    if ((ix | lx) == 0) {
        double fabsV;
        fabs(x, &fabsV);

        *result = -1.0 / fabsV;
        return;
    }
    if (ix >= 0x7ff00000) {
        *result =  x * x;
        return;
    }
    if ((ix >>= 20) == 0) {            /* IEEE 754 logb */
        *result = -1022.0;
        return;
    }
    else {
        *result = (double) (ix - 1023);
        return;
    }
}
