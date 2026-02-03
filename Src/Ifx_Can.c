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

uint64 Ifx_Can_Node_getRxBufferNewDataUpdated(IfxCan_Can_Node *node) {
  /*
   * Check which Rx buffers have received new data.
   * Set the corresponding bits in rx_buffer.
   * Invoke the event with the rx_buffer bitmask if any Rx buffer has new data.
   * Do not assume that only one Rx buffer has new data.
   */
  uint64 rx_buffer = 0ULL;
  for (IfxCan_RxBufferId rx_buffer_id = IfxCan_RxBufferId_0; rx_buffer_id <= IfxCan_RxBufferId_63; rx_buffer_id++) {
    if (IfxCan_Node_isRxBufferNewDataUpdated(node->node, rx_buffer_id)) {
      rx_buffer |= 1ULL << rx_buffer_id;
    }
  }
  return rx_buffer;
}

void Ifx_Can_Node_readRxBuffer(IfxCan_Can_Node *node, IfxCan_RxBufferId id, IfxCan_Message *message, uint32 *data) {
  message->bufferNumber = id;
  message->readFromRxFifo0 = FALSE;
  message->readFromRxFifo1 = FALSE;
  IfxCan_Can_readMessage(node, message, data);
}

void Ifx_Can_Node_readRxFifo(IfxCan_Can_Node *node, uint8_least fifo, IfxCan_Message *message, uint32 *data) {
  boolean is_fifo0 = (fifo == 0) ? TRUE : FALSE;
  message->readFromRxFifo0 = is_fifo0;
  message->readFromRxFifo1 = !is_fifo0;
  IfxCan_Can_readMessage(node, message, data);
}
