/* SPDX-License-Identifier: MIT */
/**********************************************************************************************************************
 * \file when.h
 * \copyright 2025, Roy Ratcliffe, Northumberland, United Kingdom
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
 *********************************************************************************************************************/

#ifndef LIBRARIES_CANNY_IFX_INC_WHEN_H_
#define LIBRARIES_CANNY_IFX_INC_WHEN_H_

#ifndef STRINGIZE
#define STRINGIZE(x) #x
#endif

#define WHEN_CALL(_when_, _call_)                                                                                      \
    static void _call_(void *with);                                                                                    \
    __attribute__((section(STRINGIZE(when_##_when_)), used)) static void (*const __when__##_call_)(void *with) = &_call_

#ifdef __TASKING__
#define WHEN_WITH(_when_, _with_)                                                                                      \
    {                                                                                                                  \
        extern const void (*const _lc_ub_##when_##_when_[])(void *with);                                               \
        extern const void (*const _lc_ue_##when_##_when_[])(void *with);                                               \
        for (void const (*const *call)(void *when) = _lc_ub_##when_##_when_; call < _lc_ue_##when_##_when_; call++) {  \
            (**call)(_with_);                                                                                          \
        }                                                                                                              \
    }
#endif /* __TASKING__ */

#endif /* LIBRARIES_CANNY_IFX_INC_WHEN_H_ */
