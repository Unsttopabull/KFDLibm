/* @(#)w_acos.c 1.3 95/01/18 */
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
 * wrap_acos(x)
 */

#include "fdlibm.h"


#ifdef __STDC__
void acos(double x, double* result)		/* wrapper acos */
#else
void acos(x, result)            /* wrapper acos */
        double x;double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_acos(x, result);
    return;
#else
    double z;
    __ieee754_acos(x, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(x)) {
        *result = z;
        return;
    }
    if (fabs(x) > 1.0) {
        __kernel_standard(x, x, 1, result); /* acos(|x|>1) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
