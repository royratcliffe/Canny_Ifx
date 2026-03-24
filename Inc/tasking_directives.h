/* SPDX-License-Identifier: MIT */
/*!
 * \file tasking_directives.h
 * \brief TASKING compiler directives for placing functions or variables in
 * specific sections.
 * \details This header defines a macro for the TASKING compiler that allows
 * developers to place functions or variables in specific sections of the
 * binary. The macro uses in-line assembly to declare and select the desired
 * section, and it applies the specified assembler directive to the section.
 * This is particularly useful for placing data in flash memory or for
 * organising code and data in a way that optimises performance or meets
 * specific requirements.
 */

#ifndef TASKING_DIRECTIVES_H
#define TASKING_DIRECTIVES_H

#ifdef __TASKING__

/*!
 * \brief TASKING compiler directive for placing a function or variable in a
 * specific section.
 * \param _section_ The name of the section where the function or variable
 * should be placed.
 * \param _directive_ The assembler directive to apply to the section (e.g.,
 * "word", "byte", "half", "float", "double", "asciiz", and others).
 * \param _expression_ The expression to be used with the assembler directive
 * (e.g., "0xDEADBEEF" for 4-byte expression).
 * \details This macro uses in-line assembly to place a function pointer or
 * other variable in a specific section of the binary. The section name is
 * specified by the `_section_` parameter, and the assembler directive is
 * specified by the `_directive_` and `_expression_` parameters. The `.sdecl`
 * directive declares the section with the specified attributes, and the `.sect`
 * directive selects that section for subsequent declarations. The `protect`
 * attribute ensures that the section is not removed during optimisation. This
 * macro is specific to the TASKING compiler and allows for fine-grained control
 * over the placement of data in flash memory.
 */
#define TASKING_CONST_SECTION_CONCAT_DIRECTIVE(_section_, _directive_, _expression_) \
  __asm(".sdecl\t'" #_section_ "',data,rom,concat,protect\n\
\t.sect\t'" #_section_ "'\n\
\t." #_directive_ "\t" #_expression_)

#endif /* __TASKING__ */

#endif /* TASKING_DIRECTIVES_H */
