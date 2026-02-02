/* SPDX-License-Identifier: MIT */
/*!
 * \file Ifx_Can.h
 */

#ifndef IFX_CAN_H
#define IFX_CAN_H

#include "IfxCan_Can.h"

/*!
 * \brief Initialise a CAN module.
 * \param can Pointer to the CAN handle to be initialised.
 * \param can_module Pointer to the CAN module to be initialised.
 * \details This function initialises the specified CAN module using a
 * configuration that is created on the stack. The configuration is only needed
 * during initialisation and carries a pointer to the CAN module. The module
 * initialisation function copies the configuration internally. This function
 * idempotently enables the CAN module, waiting for it to be ready.
 */
void Ifx_Can_initModule(IfxCan_Can *can, Ifx_CAN *can_module);

#endif /* IFX_CAN_H */
