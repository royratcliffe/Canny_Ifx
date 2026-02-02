#ifndef CANNY_IFX_INC_EVENT_GROUP_H_
#define CANNY_IFX_INC_EVENT_GROUP_H_

#include "Platform_Types.h"

/*!
 * \brief Event mask type.
 * \details This type defines the event mask used for event group operations.
 */
typedef unsigned int event_mask_t;

/*!
 * \brief Event group type.
 * \details This type defines the event group used for event group operations.
 */
typedef volatile event_mask_t event_group_t;

/*!
 * \brief Signals an event in the event group.
 * \details The `event_group_signal` function sets the event corresponding to
 * the specified class in the event group.
 * \param event_group Pointer to the event group to modify.
 * \param clz The class (0-31) of the event to signal.
 * \return boolean indicating whether the event was previously set.
 */
boolean event_group_signal(event_group_t *event_group, int clz);

/*!
 * \brief Synchronises events in the event group.
 * \details The `event_group_sync` function clears all events in the event group
 * and calls the provided synchronisation function for each event that was set.
 * \param event_group Pointer to the event group to synchronise.
 * \param sync Function pointer to the synchronisation function to call for each set event.
 */
void event_group_sync(event_group_t *event_group, void (*sync)(int clz));

/*!
 * \brief Sets events in the event group.
 * \details The `event_group_set` function sets the specified events in the
 * event group.
 * \param event_group Pointer to the event group to modify.
 * \param mask Mask specifying which events to set.
 * \return The previous state of the event group before setting the events.
 */
event_mask_t event_group_set(event_group_t *event_group, event_mask_t mask);

/*!
 * \brief Clears events in the event group.
 * \details The `event_group_clear` function clears the specified events in the
 * event group.
 * \param event_group Pointer to the event group to modify.
 * \param mask Mask specifying which events to clear.
 * \return The previous state of the event group before clearing the events.
 */
event_mask_t event_group_clear(event_group_t *event_group, event_mask_t mask);

#endif /* CANNY_IFX_INC_EVENT_GROUP_H_ */
