/* SPDX-License-Identifier: MIT */
/*!
 * \file lc.h
 * \brief Low-level C library definitions.
 * \details This header file contains definitions for low-level C library
 * functionalities.
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

#ifndef CANNY_IFX_LC_H_
#define CANNY_IFX_LC_H_

#include "stringify.h"

/*!
 * \brief Section used attribute.
 * \details This macro is utilised to mark a function or variable as used, ensuring
 * that it is not eliminated by the linker during optimisation.
 *
 * This is particularly useful for functions that are intended to be
 * called dynamically or registered as callbacks, ensuring they remain in the
 * final binary.
 *
 * \param _section_ The name of the section where the function or variable should be placed.
 * The name of the section should be a valid identifier and should not contain spaces or special characters.
 * Ideally, it should be a descriptive name that indicates the purpose of the section.
 * It is recommended to use a name that follows the project's naming conventions.
 * The section name is used to group related functions or variables together,
 * making it easier to manage and locate them in the binary.
 * It should be unique within the context of the binary to avoid conflicts with other sections.
 * It should use C-style naming conventions, such as using underscores to separate words.
 * The section name is used by the linker to place the function or variable in the specified section
 * and to ensure that it is not removed during the linking process.
 * \note The section name is converted to a string literal using the STRINGIFY macro.
 */
#define SECTION_USED(_section_) __attribute__((section(STRINGIFY(_section_)), used))

/*!
 * \brief Start of section.
 * \details This macro marks the start of a section for the specified
 * section name.
 *
 * \param _section_ The name of the section.
 * \note The start of section is used to determine the range of the section
 * and is typically used in conjunction with the end of section macro.
 */
#if defined(__TASKING__)
#define START_OF_SECTION(_section_) _lc_ub_##_section_
#elif defined(__GNUC__)
#define START_OF_SECTION(_section_) __start_##_section_
#endif /* __TASKING__ || __GNUC__ */

/*!
 * \brief End of section.
 * \details This macro marks the end of a section for the specified
 * section name.
 *
 * \param _section_ The name of the section.
 * \note The end of section is used to determine the range of the section
 * and is typically used in conjunction with the start of section macro.
 */
#if defined(__TASKING__)
#define END_OF_SECTION(_section_) _lc_ue_##_section_
#elif defined(__GNUC__)
#define END_OF_SECTION(_section_) __stop_##_section_
#endif /* __TASKING__ || __GNUC__ */

#endif /* CANNY_IFX_LC_H_ */