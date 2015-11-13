/* @(#)w_atan2.c 1.3 95/01/18 */
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
 * wrapper atan2(y,x)
 */

#include "fdlibm.h"


#ifdef __STDC__

void atan2(double y, double x, double* result)    /* wrapper atan2 */
#else
void atan2(y, x, result)            /* wrapper atan2 */
        double y, x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_atan2(y, x, result);
    return;
#else
    double z;
    __ieee754_atan2(y, x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x) || isnan(y)) {
        *result = z;
        return;
    }
    if (x == 0.0 && y == 0.0) {
        __kernel_standard(y, x, 3, result); /* atan2(+-0,+-0) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
