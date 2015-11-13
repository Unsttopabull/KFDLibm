/* @(#)w_cosh.c 1.3 95/01/18 */
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
 * wrapper cosh(x)
 */

#include "fdlibm.h"

#ifdef __STDC__
void cosh(double x, double* result)		/* wrapper cosh */
#else
void cosh(x,result)            /* wrapper cosh */
        double x;double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_cosh(x, result);
#else
    double z;
    __ieee754_cosh(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    if (fabs(x) > 7.10475860073943863426e+02) {
        __kernel_standard(x, x, 5, result); /* cosh overflow */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
