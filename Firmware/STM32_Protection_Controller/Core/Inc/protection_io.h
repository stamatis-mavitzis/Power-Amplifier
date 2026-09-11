#ifndef PROTECTION_IO_H
#define PROTECTION_IO_H

#include <stdint.h>
#include <stdbool.h>


void ProtectionIO_Init(void);


/* Speaker relays */

void ProtectionIO_SpeakersOn(void);
void ProtectionIO_SpeakersOff(void);


/* Pushbuttons */

bool ProtectionIO_MutePressed(void);
bool ProtectionIO_ResetPressed(void);


/* LEDs */

void ProtectionIO_UpdateLEDs(uint8_t faults,
                             bool startup_waiting);


#endif /* PROTECTION_IO_H */
