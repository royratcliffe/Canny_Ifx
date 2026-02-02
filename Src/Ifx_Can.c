/* SPDX-License-Identifier: MIT */
/*!
 * \file Ifx_Can.c
 * \brief CAN module initialisation.
 */

#include "Ifx_Can.h"

void Ifx_Can_initModule(IfxCan_Can *can, Ifx_CAN *can_module) {
  /*
   * Initialise CAN module.
   *
   * Let the configuration live on the stack as it is only needed during
   * initialisation. It carries only a pointer to the CAN module. Module
   * initialisation copies the configuration internally. It idempotently
   * enables the CAN module, waiting for it to be ready.
   */
  IfxCan_Can_Config can_config;
  IfxCan_Can_initModuleConfig(&can_config, can_module);
  IfxCan_Can_initModule(can, &can_config);
}
