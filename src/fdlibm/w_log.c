/* @(#)w_log.c 1.3 95/01/18 */
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
 * wrapper log(x)
 */

#include "fdlibm.h"


#ifdef __STDC__
void log(double x, double* result)		/* wrapper log */
#else
void log(x, result)            /* wrapper log */
        double x; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_log(x, result);
    return;
#else
    double z;
    __ieee754_log(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x) || x > 0.0) {
        *result = z;
        return;
    }
    if (x == 0.0) {
        __kernel_standard(x, x, 16, result); /* log(0) */
        return;
    }
    else {
        __kernel_standard(x, x, 17, result);
        return;
    } /* log(x<0) */
#endif
}
