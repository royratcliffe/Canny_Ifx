#include "event_group.h"
#include "swapmsk_w.h"

#include "IfxCpu.h"

/*!
 * \brief Signals an event in the event group.
 * \details The `event_group_signal` function sets the event corresponding to
 * the specified class in the event group.
 * \param event_group Pointer to the event group to modify.
 * \param clz The class (0-31) of the event to signal.
 * \return boolean indicating whether the event was previously set.
 */
boolean event_group_signal(event_group_t *event_group, int clz) { return (event_group_set(event_group, 1 << clz) >> clz) & 1U != 0U; }

/*!
 * \brief Synchronises events in the event group.
 * \details The `event_group_sync` function clears all events in the event group
 * and calls the provided synchronisation function for each event that was set.
 * \param event_group Pointer to the event group to synchronise.
 * \param sync Function pointer to the synchronisation function to call for each set event.
 */
void event_group_sync(event_group_t *event_group, void (*sync)(int clz)) {
  event_mask_t mask = event_group_clear(event_group, 0xffffffffUL);
  for (int clz; (clz = __clz(mask)) < 32; mask &= ~(1 << clz)) {
    sync(clz);
  }
}

event_mask_t event_group_set(event_group_t *event_group, event_mask_t mask) { return Ifx__swapAndMask(event_group, 0xffffffffUL, mask); }

event_mask_t event_group_clear(event_group_t *event_group, event_mask_t mask) { return Ifx__swapAndMask(event_group, 0x00000000UL, mask); }
