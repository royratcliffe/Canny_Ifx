/* SPDX-License-Identifier: MIT */
/*!
 * \file Ifx_Can.h
 */

#ifndef IFX_CAN_H
#define IFX_CAN_H

#include "IfxCan_Can.h"
#include "Ifx_Isr.h"
#include "when.h"

#include <stdarg.h>

/*!
 * \brief Macro to define an interrupt service routine (ISR) for CAN node Rx buffer interrupts.
 * \param _isr_ Name of the ISR function.
 * \param _cpu_ CPU number, 0 through 3.
 * \param _pri_ Interrupt priority level.
 * \param _node_ Pointer to the CAN node handle.
 * \param _line_ Interrupt line number.
 * \details This macro declares an interrupt service routine (ISR) for handling
 * CAN node Rx buffer interrupts. It sets up the ISR with the specified name,
 * vector table number, priority level, and CAN node handle. The ISR clears
 * the interrupt flag and checks which Rx buffers have received new data.
 */
#define IFX_CAN_REINT_ISR(_isr_, _cpu_, _pri_, _node_, _line_)                              \
  CAUSES(can_node_config, can_node_config_##_isr_);                                         \
  static void can_node_config_##_isr_(void *with, ...) {                                    \
    if ((void *)(_node_) == with) {                                                         \
      va_list va;                                                                           \
      va_start(va, with);                                                                   \
      IfxCan_Can_NodeConfig *can_node_config = va_arg(va, IfxCan_Can_NodeConfig *);         \
      can_node_config->interruptConfig.messageStoredToDedicatedRxBufferEnabled = TRUE;      \
      can_node_config->interruptConfig.reint.priority = _pri_;                              \
      can_node_config->interruptConfig.reint.interruptLine = IfxCan_InterruptLine_##_line_; \
      can_node_config->interruptConfig.reint.typeOfService = IfxSrc_Tos_cpu##_cpu_;         \
    }                                                                                       \
  }                                                                                         \
  IFX_ISR(_isr_, _cpu_, _pri_, _node_)

#define IFX_CAN_RXF0N_ISR(_isr_, _cpu_, _pri_, _node_, _line_)                              \
  CAUSES(can_node_config, can_node_config_##_isr_);                                         \
  static void can_node_config_##_isr_(void *with, ...) {                                    \
    if ((void *)(_node_) == with) {                                                         \
      va_list va;                                                                           \
      va_start(va, with);                                                                   \
      IfxCan_Can_NodeConfig *can_node_config = va_arg(va, IfxCan_Can_NodeConfig *);         \
      can_node_config->interruptConfig.rxFifo0NewMessageEnabled = TRUE;                     \
      can_node_config->interruptConfig.rxf0n.priority = _pri_;                              \
      can_node_config->interruptConfig.rxf0n.interruptLine = IfxCan_InterruptLine_##_line_; \
      can_node_config->interruptConfig.rxf0n.typeOfService = IfxSrc_Tos_cpu##_cpu_;         \
    }                                                                                       \
  }                                                                                         \
  void _isr_(IfxCan_Can_Node *node);                                                        \
  IFX_ISR(_isr_, _cpu_, _pri_, _node_)

/*!
 * \brief Macro to define an interrupt service routine (ISR) for CAN node Rx buffer interrupts.
 * \param _cpu_ CPU number.
 * \param _pri_ Interrupt priority level.
 * \param _node_ Pointer to the CAN node handle.
 * \param _line_ Interrupt line number.
 * \details This macro declares an interrupt service routine (ISR) for handling
 * CAN node Rx buffer interrupts. It sets up the ISR with the specified name,
 * vector table number, priority level, and CAN node handle. The ISR clears
 * the interrupt flag and checks which Rx buffers have received new data,
 * invoking the appropriate event if any Rx buffer has new data.
 */
#define IFX_CAN_NODE_REINT_ISR(_cpu_, _pri_, _node_, _line_) IFX_CAN_REINT_ISR(Ifx_Can_Node_rxBufferIsr, _cpu_, _pri_, _node_, _line_)

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

/*!
 * \brief Get Rx buffers with new data updated.
 * \details This function checks which Rx buffers have received new data and
 * returns a bitmask indicating the buffers with new data.
 * \param node Pointer to the CAN node handle.
 * \return A 64-bit bitmask where each bit represents an Rx buffer. A bit is
 * set to 1 if the corresponding Rx buffer has received new data, otherwise it
 * is set to 0.
 */
uint64 Ifx_Can_Node_getRxBufferNewDataUpdated(IfxCan_Can_Node *node);

/*!
 * \brief Load Rx buffers with new data updated.
 * \details This function loads the status of Rx buffers that have received
 * new data from the CAN node's NDAT registers, 1 and 2.
 * \param n Base address of the CAN node module.
 * \return A 64-bit bitmask where each bit represents an Rx buffer. A bit is
 * set to 1 if the corresponding Rx buffer has received new data, otherwise it
 * is set to 0.
 */
IFX_INLINE uint64 Ifx__Can_Node_ldNDAT(Ifx_CAN_N *n) { return n->NDAT1.U | ((uint64)n->NDAT2.U << 32); }

/*!
 * \brief Load Rx buffers with new data updated.
 * \details This function loads the status of Rx buffers that have received
 * new data from the CAN node's NDAT registers.
 * \param node Pointer to the CAN node handle.
 * \return A 64-bit bitmask where each bit represents an Rx buffer. A bit is
 * set to 1 if the corresponding Rx buffer has received new data, otherwise it
 * is set to 0.
 */
IFX_INLINE uint64 Ifx_Can_Node_loadRxBufferNewDataUpdated(IfxCan_Can_Node *node) { return Ifx__Can_Node_ldNDAT(node->node); }

/*!
 * \brief Read a message from a dedicated Rx buffer.
 * \details This function reads a message from the specified dedicated Rx
 * buffer of the CAN node. It sets up the message structure to read from the
 * specified Rx buffer and invokes the generic message read function.
 * \param node Pointer to the CAN node handle.
 * \param id Identifier of the Rx buffer to read from.
 * \param message Pointer to the message structure to be filled with the
 * received message metadata.
 * \param data Pointer to the data array to be filled with the received message
 * data.
 */
void Ifx_Can_Node_readRxBuffer(IfxCan_Can_Node *node, IfxCan_RxBufferId id, IfxCan_Message *message, uint32 *data);

/*!
 * \brief Read a message from an Rx FIFO.
 * \details This function reads a message from the specified Rx FIFO of the
 * CAN node. It sets up the message structure to read from the specified Rx
 * FIFO and invokes the generic message read function.
 * \param node Pointer to the CAN node handle.
 * \param fifo Rx FIFO number (0 or 1) to read from.
 * \param message Pointer to the message structure to be filled with the
 * received message metadata.
 * \param data Pointer to the data array to be filled with the received message
 * data.
 */
void Ifx_Can_Node_readRxFifo(IfxCan_Can_Node *node, uint8_least fifo, IfxCan_Message *message, uint32 *data);

/*!
 * \brief Interrupt service routine for CAN node Rx buffer interrupts.
 * \details This function serves as the interrupt service routine (ISR) for
 * CAN node Rx buffer interrupts. It clears the interrupt flag and checks
 * which Rx buffers have received new data, invoking the appropriate event if
 * any Rx buffer has new data.
 * \param node Pointer to the CAN node handle.
 */
void Ifx_Can_Node_rxBufferIsr(IfxCan_Can_Node *node);

#endif /* IFX_CAN_H */
