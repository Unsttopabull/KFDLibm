/* @(#)w_fmod.c 1.3 95/01/18 */
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
 * wrapper fmod(x,y)
 */

#include "fdlibm.h"


#ifdef __STDC__
void fmod(double x, double y, double* result)	/* wrapper fmod */
#else
void fmod(x, y, result)        /* wrapper fmod */
        double x, y; double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_fmod(x,y, result);
    return;
#else
    double z;
    __ieee754_fmod(x, y, &z);
    if (_LIB_VERSION == _IEEE_ || isnan(y) || isnan(x)) {
        *result = z;
        return;
    }
    if (y == 0.0) {
        __kernel_standard(x, y, 27, result); /* fmod(x,0) */
        return;
    }
    else {
        *result = z;
        return;
    }
#endif
}
