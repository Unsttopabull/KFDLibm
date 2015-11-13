/* @(#)w_log10.c 1.3 95/01/18 */
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
 * wrapper log10(X)
 */

#include "fdlibm.h"


#ifdef __STDC__
void log10(double x, double* result)		/* wrapper log10 */
#else
void log10(x, result)            /* wrapper log10 */
        double x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_log10(x,result);
    return;
#else
    double z;
    __ieee754_log10(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    if (x <= 0.0) {
        if (x == 0.0) {
            __kernel_standard(x, x, 18, result); /* log10(0) */
            return;
        }
        else {
            __kernel_standard(x, x, 19, result);
            return;
        } /* log10(x<0) */
    }
    else {
        *result = z;
        return;
    }
#endif
}
