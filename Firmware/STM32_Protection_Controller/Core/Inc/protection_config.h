#ifndef PROTECTION_CONFIG_H
#define PROTECTION_CONFIG_H


/* =========================================================
 * TIMING
 * ========================================================= */

/* Wait before speakers may be connected */
#define STARTUP_DELAY_MS          3000U

/* Protection system sampling interval */
#define SAMPLE_INTERVAL_MS       10U

/* Pushbutton debounce */
#define BUTTON_DEBOUNCE_MS       30U

/* ADC samples averaged for each measurement */
#define ADC_AVERAGE_SAMPLES      8U


/* =========================================================
 * TEMPERATURE PROTECTION
 *
 * 10 kOhm NTC + 10 kOhm pull-up
 * ========================================================= */

/* Approx. 100 °C trip point */
#define TEMP_TRIP_ADC            261U

/* Approx. 90 °C reset point */
#define TEMP_RESET_ADC           342U

/* Temperature sensor failure limits */
#define TEMP_SHORT_ADC           25U
#define TEMP_OPEN_ADC            4070U


/* =========================================================
 * DC OFFSET PROTECTION
 * ========================================================= */

/* ADC value corresponding approximately to 0 V amplifier DC */
#define DC_CENTER_ADC            1982.0f

/* ADC counts per volt at amplifier output */
#define DC_COUNTS_PER_VOLT       40.04f


/* Normal DC fault */
#define DC_TRIP_VOLTAGE          1.0f
#define DC_TRIP_TIME_MS          100U


/* Severe DC fault */
#define DC_FAST_TRIP_VOLTAGE     5.0f
#define DC_FAST_TRIP_TIME_MS     10U


/* Maximum DC offset allowed before reconnecting speakers */
#define DC_SAFE_VOLTAGE          0.5f


#endif /* PROTECTION_CONFIG_H */
