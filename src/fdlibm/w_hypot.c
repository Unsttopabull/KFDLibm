/* @(#)w_hypot.c 1.3 95/01/18 */
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
 * wrapper hypot(x,y)
 */

#include "fdlibm.h"


#ifdef __STDC__
void hypot(double x, double y, double* result)/* wrapper hypot */
#else
void hypot(x, y, result)        /* wrapper hypot */
        double x, y; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_hypot(x,y, result);
    return;
#else
    double z;
    __ieee754_hypot(x, y, &z);
    if (_LIB_VERSION == _IEEE_) {
        *result = z;
        return;
    }
    if ((!finite(z)) && finite(x) && finite(y)) {
        __kernel_standard(x, y, 4, result); /* hypot overflow */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
