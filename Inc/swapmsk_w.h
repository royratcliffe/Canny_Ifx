/*!
 * \file swapmskw.h
 * \brief Atomic swap with mask operation.
 */

#ifndef SWAPMSK_W_H_
#define SWAPMSK_W_H_

#include "Compilers.h"

/*!
 * \brief Atomic swap with mask operation
 * \details This function performs an atomic swap with mask operation on a
 * 32-bit value located at the specified address. It swaps the value at the
 * address with the provided value, applying the specified mask to determine
 * which bits to swap.
 * \param address Pointer to the 32-bit value to be swapped.
 * \param value The new value to be swapped in.
 * \param mask A mask that specifies which bits to swap.
 * \return The original value before the swap operation.
 */
#if defined(__TASKING__)
IFX_INLINE unsigned int Ifx__swapAndMask(unsigned int volatile *address, unsigned int value, unsigned int mask) { return __swapmskw(address, value, mask); }
#elif defined(__GNUC__)
IFX_INLINE unsigned int Ifx__swapAndMask(unsigned int volatile *address, unsigned int value, unsigned int mask) {
  __extension__ unsigned long long reg64 = value | (unsigned long long)mask << 32;
  __asm__ __volatile__("swapmsk.w [%[addr]]0, %A[reg]" : [reg] "+d"(reg64) : [addr] "a"(address) : "memory");
  return reg64;
}
#endif

#endif /* SWAPMSK_W_H_ */
