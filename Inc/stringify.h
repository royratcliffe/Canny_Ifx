/* SPDX-License-Identifier: MIT */
/*!
 * \file stringify.h
 * \brief Stringify macro definitions.
 * \details This header file contains macro definitions for converting tokens
 * into string literals.
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

#ifndef CANNY_IFX_STRINGIFY_H_
#define CANNY_IFX_STRINGIFY_H_

/*!
 * \brief Converts the macro argument into a string literal.
 * \details This macro takes its argument and converts it into a string literal.
 * It is commonly used in preprocessor directives or attributes where the C code
 * requires the string-ification of some arbitrary token.
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
 * \brief Expands the macro argument and then converts it into a string literal.
 * \details This macro first expands its argument if it is a macro itself,
 * and then converts the result into a string literal. This is useful when
 * you want to stringify the value of a macro rather than the macro name.
 * \param x The token or value to be expanded and then converted to a string literal.
 */
#define XSTRINGIFY(x) STRINGIFY(x)

#endif /* CANNY_IFX_STRINGIFY_H_ */
