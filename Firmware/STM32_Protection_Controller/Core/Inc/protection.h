#ifndef PROTECTION_H
#define PROTECTION_H

#include <stdint.h>


/* =========================================================
 * PROTECTION FAULT FLAGS
 * ========================================================= */

typedef enum
{
    FAULT_NONE         = 0x00,
    FAULT_TEMP1_SENSOR = 0x01,
    FAULT_TEMP2_SENSOR = 0x02,
    FAULT_OVERTEMP     = 0x04,
    FAULT_DC           = 0x08

} ProtectionFault;


/* =========================================================
 * PUBLIC FUNCTIONS
 * ========================================================= */

void Protection_Init(void);

void Protection_Task(void);


#endif /* PROTECTION_H */
