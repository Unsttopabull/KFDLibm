/* @(#)w_exp.c 1.4 04/04/22 */
/*
 * ====================================================
 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* 
 * wrapper exp(x)
 */

#include "fdlibm.h"

#ifdef __STDC__
static const double
#else
static double
#endif
        o_threshold = 7.09782712893383973096e+02,  /* 0x40862E42, 0xFEFA39EF */
        u_threshold = -7.45133219101941108420e+02;  /* 0xc0874910, 0xD52D3051 */

#ifdef __STDC__
void exp(double x, double* result)		/* wrapper exp */
#else
void exp(x,result)            /* wrapper exp */
        double x;double* result;
#endif
{
#ifdef _IEEE_LIBM
    __ieee754_exp(x,result);
    return;
#else
    double z;
    __ieee754_exp(x, &z);
    if (_LIB_VERSION == _IEEE_) {
        *result = z;
        return;
    }
    if (finite(x)) {
        if (x > o_threshold) {
            __kernel_standard(x, x, 6, result); /* exp overflow */
            return;
        }
        else if (x < u_threshold) {
            __kernel_standard(x, x, 7, result);
            return;
        } /* exp underflow */
    }
    *result = z;
    return;
#endif
}
