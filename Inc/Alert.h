/*!
 * \file alert.h
 * \brief Alert urgency level definitions.
 * \details This header file defines the enumeration for alert urgency levels used in the system.
 * The alert urgency levels indicate the severity of an alert and guide the appropriate response.
 */

#ifndef ALERT_H
#define ALERT_H

/*!
 * \brief Alert urgency levels.
 * \details Defines the urgency levels for alerts in the system. Each level
 * indicates the severity of the alert and the recommended response in
 * increasing order of urgency, as follows:
 * - Alert_urgency_memo: Informational message, no immediate action required.
 * - Alert_urgency_advisory: Advisory message, action recommended but not critical.
 * - Alert_urgency_caution: Caution message, action needed soon to prevent issues.
 * - Alert_urgency_warning: Warning message, immediate action required to avoid hazards.
 */
enum Alert_urgency { Alert_urgency_memo, Alert_urgency_advisory, Alert_urgency_caution, Alert_urgency_warning };

#endif /* ALERT_H */
