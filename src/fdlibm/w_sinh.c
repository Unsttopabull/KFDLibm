/* @(#)w_sinh.c 1.3 95/01/18 */
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
 * wrapper sinh(x)
 */

#include "fdlibm.h"

#ifdef __STDC__
void sinh(double x, double* result)		/* wrapper sinh */
#else
void sinh(x, result)            /* wrapper sinh */
        double x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_sinh(x, result);
    return;
#else
    double z;
    __ieee754_sinh(x, &z);
    if (_LIB_VERSION == _IEEE_) {
        *result = z;
        return;
    }
    if (!finite(z) && finite(x)) {
        __kernel_standard(x, x, 25, result); /* sinh overflow */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
