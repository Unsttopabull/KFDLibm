/* @(#)s_ldexp.c 1.3 95/01/18 */
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

#include "fdlibm.h"
#include <errno.h>

#ifdef __STDC__
void ldexp(double value, int exp, double* result)
#else
void ldexp(value, exp, result)
        double value; int exp; double* result;
#endif
{
    if (!finite(value) || value == 0.0) {
        *result = value;
        return;
    }
    scalbn(value, exp, &value);
    if (!finite(value) || value == 0.0) {
        errno = ERANGE;
    }
    *result = value;
    return;
}
