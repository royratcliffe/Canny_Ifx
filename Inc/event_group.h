#ifndef CANNY_IFX_INC_EVENT_GROUP_H_
#define CANNY_IFX_INC_EVENT_GROUP_H_

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
