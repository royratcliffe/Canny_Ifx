#ifndef CANNY_IFX_INC_IFX_SRC_H
#define CANNY_IFX_INC_IFX_SRC_H 1

/*!
 * \brief Macro to map type of service to vector table number.
 * \param tos Type of service.
 * \return Corresponding interrupt vector table number.
 * \details This macro maps the given type of service to the corresponding
 * interrupt vector table number. It supports the following types of service:
 * IfxSrc_Tos_cpu0 (0), IfxSrc_Tos_cpu1 (1), IfxSrc_Tos_cpu2 (2), and IfxSrc_Tos_dma (3).
 */
#define IFX_SRC_TOS_VECTAB(tos) ((tos) == IfxSrc_Tos_cpu0 ? 0 : ((tos) == IfxSrc_Tos_cpu1 ? 1 : ((tos) == IfxSrc_Tos_cpu2 ? 2 : 3)))

#endif /* CANNY_IFX_INC_IFX_SRC_H */
