/* SPDX-License-Identifier: MIT */
/*!
 * \file Ifx_CPU.h
 *
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
 * \author Roy Ratcliffe <roy@ratcliffe.me>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
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

#ifndef CANNY_IFX_INC_IFX_CPU_H_
#define CANNY_IFX_INC_IFX_CPU_H_

#include "IfxCpu.h"

/*!
 * \brief Get the core address.
 * \details This function retrieves and caches the address of the current CPU
 * core. This is useful for accessing core-specific registers and memory. It
 * ensures that the address is only fetched once, improving performance by
 * avoiding repeated calls to IfxCpu_getAddress. This function is typically used
 * in scenarios where the core address is needed multiple times, such as in
 * interrupt handlers or critical sections.
 *
 * \return Pointer to the current CPU core structure.
 */
Ifx_CPU *IfxCpu_getCoreAddress(void);

#endif /* CANNY_IFX_INC_IFX_CPU_H_ */
