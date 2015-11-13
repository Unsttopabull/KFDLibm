/* @(#)w_sqrt.c 1.3 95/01/18 */
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
 * wrapper sqrt(x)
 */

#include "fdlibm.h"

#ifdef __STDC__
void sqrt(double x, double* result)		/* wrapper sqrt */
#else
void sqrt(x,result)            /* wrapper sqrt */
        double x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_sqrt(x, result);
    return;
#else
    double z;
    __ieee754_sqrt(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    if (x < 0.0) {
        __kernel_standard(x, x, 26, result); /* sqrt(negative) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
