#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint16_t temp1_adc;
    uint16_t temp2_adc;

    uint16_t dc_left_adc;
    uint16_t dc_right_adc;

} SensorData;


void Sensors_Init(void);

bool Sensors_Read(SensorData *data);

bool Sensors_TempValid(uint16_t adc);

bool Sensors_OverTemperature(uint16_t adc);

bool Sensors_TempCoolForReset(uint16_t adc);

float Sensors_DCVoltage(uint16_t adc);


#endif /* SENSORS_H */
