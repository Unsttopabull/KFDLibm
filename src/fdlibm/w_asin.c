/* @(#)w_asin.c 1.3 95/01/18 */
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
 * wrapper asin(x)
 */


#include "fdlibm.h"


#ifdef __STDC__
void asin(double x, double* result)		/* wrapper asin */
#else
void asin(x, result)            /* wrapper asin */
        double x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_asin(x, result);
    return;
#else
    double z;
    __ieee754_asin(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }

    double fabsV;
    fabs(x, &fabsV);

    if (fabsV > 1.0) {
        __kernel_standard(x, x, 2, result); /* asin(|x|>1) */
        return;
    }
    else {
        *result =z;
        return;
    }
#endif
}
