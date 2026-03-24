#include "event_group.h"
#include "swapmsk_w.h"

#include "IfxCpu.h"

boolean event_group_signal(event_group_t *event_group, int clz) { return ((event_group_set(event_group, 1 << clz) >> clz) & 1U) != 0U; }

void event_group_sync(event_group_t *event_group, void (*sync)(int clz, va_list va), ...) {
  va_list va;
  va_start(va, sync);
  event_mask_t mask = event_group_clear(event_group, 0xffffffffUL);
  /*
   * CLZ counts leading zeros, so we can use it to find the lowest set bit in the mask.
   * Leading zeros are counted from the most significant bit (bit 31) to the least significant bit (bit 0).
   * Thus, __clz(mask) returns the index of the first set bit (0-31) or 32 if no bits are set.
   */
  for (int clz; (clz = __clz(mask)) < 32; mask &= ~(0x80000000UL >> clz)) {
    sync(31 - clz, va);
  }
}

event_mask_t event_group_set(event_group_t *event_group, event_mask_t mask) { return Ifx__swapAndMask(event_group, 0xffffffffUL, mask); }

event_mask_t event_group_clear(event_group_t *event_group, event_mask_t mask) { return Ifx__swapAndMask(event_group, 0x00000000UL, mask); }
