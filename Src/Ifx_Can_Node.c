#include "Ifx_Can_Node.h"

static void Ifx_Can_Node_enableGroupInterrupt(IfxCan_GroupInterruptConfig *config, Ifx_Priority prio, IfxCan_InterruptLine line, IfxSrc_Tos tos);

void Ifx_Can_Node_enableReint(IfxCan_Can_NodeConfig *config, Ifx_Priority prio, IfxCan_InterruptLine line, IfxSrc_Tos tos) {
  config->interruptConfig.messageStoredToDedicatedRxBufferEnabled = TRUE;
  Ifx_Can_Node_enableGroupInterrupt(&config->interruptConfig.reint, prio, line, tos);
}

/*!
 * \brief Enables the Transmission Control Interrupt for the CAN node and configures the group interrupt.
 * \param config Pointer to the CAN node configuration structure.
 */
void Ifx_Can_Node_enableTraco(IfxCan_Can_NodeConfig *config, Ifx_Priority prio, IfxCan_InterruptLine line, IfxSrc_Tos tos) {
  config->interruptConfig.transmissionCompletedEnabled = TRUE;
  Ifx_Can_Node_enableGroupInterrupt(&config->interruptConfig.traco, prio, line, tos);
}

void Ifx_Can_Node_enableGroupInterrupt(IfxCan_GroupInterruptConfig *config, Ifx_Priority prio, IfxCan_InterruptLine line, IfxSrc_Tos tos) {
  config->priority = prio;
  config->interruptLine = line;
  config->typeOfService = tos;
}
