/**********************************************************************************************************************
 * \file compare_float.h
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 *
 * SPDX-License-Identifier: MIT
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
 *********************************************************************************************************************/

#ifndef INC_COMPARE_FLOAT_H_
#define INC_COMPARE_FLOAT_H_

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*!
 * \brief Compares two floating-point numbers by reference.
 * \details Avoids comparing equality in floating-point space.
 * Compiler warnings arise when comparing floating equality.
 * Compare greater than or less than. Default to equality if neither
 * greater or less.
 *
 * The implementation:
 *
 * -   avoids direct equality of floating-point numbers for a stable
 *     three-way float comparison;
 *
 * -   explicitly checks for Not a Number (NaN) values.
 *
 * Two NaN values are equal; NaN equals NaN, naturally. Otherwise, NaN
 * precedes all numbers. NaN compared to N yields "less" when compared.
 * Some floating-point N compared to NaN gives a "greater" comparison.
 *
 * Answers -1 for NaN with N, 0 for NaN and NaN, and 1 for N with NaN.
 *
 * Does **not** compare with epsilon tolerance.
 * \param left Pointer to left-hand float in 32 bits.
 * \param right Pointer to right-hand 32-bit float.
 * \retval -1 if left is less than right.
 * \retval 1 if right is less than left.
 * \retval 0 if left and right default to equality.
 */
int compare_float(const void *left, const void *right);

/*!
 * \brief Compares two floating-point numbers by epsilon threshold.
 * \details
 * Compares two floating-point numbers by the epsilon threshold. The two
 * numbers compare equally if their difference by subtraction proves to be
 * less than the standard floating-point epsilon limit.
 * \param left Pointer to left-hand float in 32 bits.
 * \param right Pointer to right-hand 32-bit float.
 * \retval 0 if left and right have epsilon equality.
 * \retval -1 if left is less than right.
 * \retval 1 if right is less than left.
 */
int compare_float_epsilon(const void *left, const void *right);

#endif /* INC_COMPARE_FLOAT_H_ */
