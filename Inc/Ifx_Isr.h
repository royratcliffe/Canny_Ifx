#ifndef IFX_ISR_H
#define IFX_ISR_H 1

#include "IfxCpu.h"

/*!
 * \brief Macro to define an interrupt service routine (ISR).
 * \param _isr_ Name of the ISR function.
 * \param _cpu_ CPU number.
 * \param _pri_ Interrupt priority level.
 * \param ... Additional arguments to be passed to the ISR function.
 */
#define IFX_ISR(_isr_, _cpu_, _pri_, ...) \
  IFX_INTERRUPT(cpu##_cpu_##_pri##_pri_##_isr, _cpu_, _pri_) { _isr_(__VA_ARGS__); }

#endif /* IFX_ISR_H */
