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

#include "Ifx_Cpu.h"

/*!
 * \brief Clone attribute.
 * \details This attribute is used to mark a variable as a clone, indicating
 * that it lives in core-associated local memory. Cloned indicates that code or
 * data is placed in the local scratchpad memory of each compatible core, or a
 * designated core, allowing the core to access it as private memory.
 */
#ifdef __TASKING__
#define IFX_CLONE __clone
#else
#define IFX_CLONE
#endif /* __TASKING__ */

Ifx_CPU *IfxCpu_getCoreAddress(void) {
    IFX_CLONE static Ifx_CPU *s_cpu;
    if (s_cpu == NULL_PTR)
        s_cpu = IfxCpu_getAddress(IfxCpu_getCoreIndex());
    return s_cpu;
}
