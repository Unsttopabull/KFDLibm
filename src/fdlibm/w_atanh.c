/* @(#)w_atanh.c 1.3 95/01/18 */
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
 * wrapper atanh(x)
 */

#include "fdlibm.h"


#ifdef __STDC__
void atanh(double x, double* result)		/* wrapper atanh */
#else
void atanh(x, result)            /* wrapper atanh */
        double x;double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_atanh(x, result);
    return;
#else
    double z, y;
    __ieee754_atanh(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    fabs(x, &y);
    if (y >= 1.0) {
        if (y > 1.0) {
            __kernel_standard(x, x, 30, result); /* atanh(|x|>1) */
            return;
        }
        else {
            __kernel_standard(x, x, 31, result);
            return;
        } /* atanh(|x|==1) */
    }
    else {
        *result = z;
        return;
    }
#endif
}
