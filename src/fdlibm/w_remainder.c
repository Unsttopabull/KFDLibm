/* @(#)w_remainder.c 1.3 95/01/18 */
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
 * wrapper remainder(x,p)
 */

#include "fdlibm.h"

#ifdef __STDC__
void remainder(double x, double y, double* result)	/* wrapper remainder */
#else
void remainder(x, y, result)            /* wrapper remainder */
        double x, y; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_remainder(x,y, result);
    return;
#else
    double z;
    __ieee754_remainder(x, y, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(y)) {
        *result = z;
        return;
    }
    if (y == 0.0) {
        __kernel_standard(x, y, 28, result); /* remainder(x,0) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
