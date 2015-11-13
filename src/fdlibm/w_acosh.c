/* @(#)w_acosh.c 1.3 95/01/18 */
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

/* 
 * wrapper acosh(x)
 */

#include "fdlibm.h"

#ifdef __STDC__
void acosh(double x, double* result)		/* wrapper acosh */
#else
void acosh(x,result)            /* wrapper acosh */
        double x;double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_acosh(x, result);
    return;
#else
    double z;
    z = __ieee754_acosh(x);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
    }
    if (x < 1.0) {
        __kernel_standard(x, x, 29, result); /* acosh(x<1) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
