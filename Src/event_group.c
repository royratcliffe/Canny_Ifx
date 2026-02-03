#include "event_group.h"
#include "swapmsk_w.h"

#include "IfxCpu.h"

boolean event_group_signal(event_group_t *event_group, int clz) { return ((event_group_set(event_group, 1 << clz) >> clz) & 1U) != 0U; }

void event_group_sync(event_group_t *event_group, void (*sync)(event_group_t *event_group, int clz)) {
  event_mask_t mask = event_group_clear(event_group, 0xffffffffUL);
  for (int clz; (clz = __clz(mask)) < 32; mask &= ~(1 << clz)) {
    sync(event_group, clz);
  }
}

event_mask_t event_group_set(event_group_t *event_group, event_mask_t mask) { return Ifx__swapAndMask(event_group, 0xffffffffUL, mask); }

event_mask_t event_group_clear(event_group_t *event_group, event_mask_t mask) { return Ifx__swapAndMask(event_group, 0x00000000UL, mask); }
