/* SPDX-License-Identifier: MIT */
/*!
 * \file when.h
 * \details Fairly advanced C preprocessor macros used for modular registration
 * in a callback framework that utilises an automatic *compile-time*
 * registration mechanism for embedded architectures.
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

#ifndef WHEN_H_
#define WHEN_H_

#include "lc.h"

/*!
 * \brief Whenever something happens, do what.
 * \details This macro defines a function that is called when a specific event
 * occurs. It is used to register a callback function that will be executed when
 * the specified event occurs. The function is placed in a specific section of
 * the binary, allowing it to be discovered and executed at runtime.
 * \param _when_ The name of the event that triggers the callback.
 * \param _what_ The name of the function to be called when the event occurs.
 */
#define WHEN_WHAT(_when_, _what_)                                                                                                                              \
  static inline void __##_when_##_with(void *with, ...) { WHEN_WITH(_when_, with); }                                                                           \
  static void _what_(void *with, ...);                                                                                                                         \
  SECTION_USED(when_##_when_) static void (*const __when__##_what_)(void *with, ...) = &_what_

/*!
 * \brief When something happened, do something with it.
 * \details This macro defines a function that is called when a specific event occurs.
 * It registers the function in a dedicated section of the binary, so the system can
 * discover and execute it at runtime. Use this macro in modular callback frameworks
 * to register multiple handlers for the same event, enabling flexible and extensible
 * event handling.
 *
 * The implementation iterates over all registered callback functions for the
 * specified event and calls each one with the provided argument.
 *
 * For the TASKING compiler, the `_lc_ub_` and `_lc_ue_` prefixes mark the start and
 * end of the callback list for the event. The `extern` declarations make the function
 * pointers visible across translation units for correct linker resolution.
 *
 * For the GCC compiler, the `__start_` and `__stop_` prefixes mark the start and end
 * of the callback list for the event.
 *
 * \param _when_ The name of the event that triggers the callback.
 * \param ... The arguments to be passed to the callback function when the
 * event occurs.
 * \note This macro is designed to work with compilers that support specific
 * section attributes, such as the TASKING or GCC compilers. It uses weak
 * symbols to allow for multiple definitions of the same function without
 * causing linker errors.
 */
#if defined(__TASKING__)
#define WHEN_WITH(_when_, ...)                                                                                                                                 \
  do {                                                                                                                                                         \
    extern void (*const _lc_ub_##when_##_when_[])(void *with, ...);                                                                                            \
    extern void (*const _lc_ue_##when_##_when_[])(void *with, ...);                                                                                            \
    for (void (*const *what)(void *with, ...) = _lc_ub_##when_##_when_; what < _lc_ue_##when_##_when_; what++) {                                               \
      (**what)(__VA_ARGS__);                                                                                                                                   \
    }                                                                                                                                                          \
  } while (0)
#elif defined(__GNUC__)
#define WHEN_WITH(_when_, ...)                                                                                                                                 \
  do {                                                                                                                                                         \
    extern void (*const __start_##when_##_when_[])(void *with, ...) __attribute__((weak));                                                                     \
    extern void (*const __stop_##when_##_when_[])(void *with, ...) __attribute__((weak));                                                                      \
    for (void (*const *what)(void *with, ...) = __start_##when_##_when_; what < __stop_##when_##_when_; what++) {                                              \
      (**what)(__VA_ARGS__);                                                                                                                                   \
    }                                                                                                                                                          \
  } while (0)
#endif /* __TASKING__ || __GNUC__ */

/*!
 * \brief Type definition for when callback functions.
 * \details This type defines the signature for callback functions that can
 * be registered using the WHEN_WHAT macro. These functions take a single
 * void pointer argument and a variable number of additional arguments.
 * \note The void pointer argument can be used to pass context or state
 * information to the callback function.
 * \see WHEN_WHAT
 * \see WHEN_WITH
 */
typedef void (*when_func_t)(void *with, ...);

#endif /* WHEN_H_ */
