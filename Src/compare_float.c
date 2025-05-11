/* SPDX-License-Identifier: MIT */
/*!
 * \file compare_float.c
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sub-license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *      The above copyright notice and this permission notice shall be included in all copies or substantial
 *      portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "compare_float.h"

#include <float.h>
#include <math.h>

int compare_float(const void *left, const void *right)
{
    float lhs = *(const float *)left, rhs = *(const float *)right;
    if (isnan(lhs))
        return isnan(rhs) ? 0 : -1;
    if (isnan(rhs))
        return 1;
    if (lhs < rhs)
        return -1;
    if (rhs < lhs)
        return 1;
    return 0;
}

int compare_float_epsilon(const void *left, const void *right)
{
    float lhs = *(const float *)left, rhs = *(const float *)right;
    if (isnan(lhs))
        return isnan(rhs) ? 0 : -1;
    if (isnan(rhs))
        return 1;
    float delta = lhs - rhs;
    if (fabsf(delta) < FLT_EPSILON)
        return 0;
    return delta < 0.0F ? -1 : 1;
}
