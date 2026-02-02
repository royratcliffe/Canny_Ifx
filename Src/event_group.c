#include "event_group.h"
#include "swapmsk_w.h"

event_mask_t event_group_set(event_group_t *event_group, event_mask_t mask) {
  return Ifx__swapAndMask(event_group, 0xffffffffUL, mask);
}

event_mask_t event_group_clear(event_group_t *event_group, event_mask_t mask) {
  return Ifx__swapAndMask(event_group, 0x00000000UL, mask);
}
