/* SPDX-License-Identifier: MIT */
/*!
 * \file when.h
 * \details Fairly advanced C preprocessor macros used for modular
 * registration in a callback framework that utilises an automatic
 * *compile-time* registration mechanism for embedded architectures.
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
 */

#ifndef CANNY_IFX_INC_WHEN_H_
#define CANNY_IFX_INC_WHEN_H_

/*!
 * \brief Converts the macro argument into a string literal.
 * \details This macro takes its argument and converts it into a string literal.
 * It is commonly used in preprocessor directives or attributes where the C code
 * requires the string-ifying of some arbitrary token.
 *
 * Take an example:
 * \code
 * #define VERSION 1.0
 * // the following will expand to "1.0"
 * const char *version_string = STRINGIFY(VERSION);
 * \endcode
 *
 * \param x The token or value to be converted to a string literal.
 */
#ifndef STRINGIFY
#define STRINGIFY(x) #x
#endif

/*!
 * \brief Whenever something happens, do what.
 */
#define WHEN_WHAT(_when_, _what_)                                                                                      \
    static inline void __##_when_##_with(void *with) { WHEN_WITH(_when_, with); }                                      \
    static void _what_(void *with);                                                                                    \
    __attribute__((section(STRINGIFY(when_##_when_)), used)) static void (*const __when__##_what_)(void *with) = &_what_

/*!
 * \brief When something happened, do something with it.
 */
#if defined(__TASKING__)
#define WHEN_WITH(_when_, _with_)                                                                                      \
    do {                                                                                                               \
        extern void (*const _lc_ub_##when_##_when_[])(void *with);                                                     \
        extern void (*const _lc_ue_##when_##_when_[])(void *with);                                                     \
        for (void (*const *what)(void *when) = _lc_ub_##when_##_when_; what < _lc_ue_##when_##_when_; what++) {        \
            (**what)(_with_);                                                                                          \
        }                                                                                                              \
    } while (0)
#elif defined(__GNUC__)
#define WHEN_WITH(_when_, _with_)                                                                                      \
    do {                                                                                                               \
        extern void (*const _start_##when_##_when_[])(void *with) __attribute__((weak));                               \
        extern void (*const _stop_##when_##_when_[])(void *with) __attribute__((weak));                                \
        for (void (*const *what)(void *when) = _start_##when_##_when_; what < _stop_##when_##_when_; what++) {         \
            (**what)(_with_);                                                                                          \
        }                                                                                                              \
    } while (0)
#endif /* __TASKING__ || __GNUC__ */

#endif /* CANNY_IFX_INC_WHEN_H_ */
