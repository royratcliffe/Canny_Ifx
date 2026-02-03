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

#endif /* IFX_CAN_H */
