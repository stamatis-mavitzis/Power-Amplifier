# STM32 Speaker Protection Controller Bill of Materials

This BOM covers the complete STM32-based speaker-protection subsystem, including the controller, stereo DC-offset sensing, dual heatsink-temperature monitoring, speaker relay drivers, status indicators, connectors, and the dedicated 12 V power supply.

> **Design note:** The DC-sensing network uses the final values **150 kΩ / 10 kΩ / 10 kΩ / 4.7 kΩ / 4.7 µF per channel**. These supersede the earlier 390 kΩ / 22 kΩ / 100 nF draft values.

| Section | References / Function | Qty | Value / Part | Description | Package / Type | Notes |
|---|---|---:|---|---|---|---|
| Controller Core | MCU1 | 1 | NUCLEO-G031K8 | STM32 Nucleo-32 development board with STM32G031K8 MCU | Nucleo-32 module | Main protection controller |
| Speaker Relay Control | K1, K2 | 2 | G2RL-1A-E-DC12 | 12 V SPST-NO speaker protection relay | THT relay | One relay per amplifier channel |
| Speaker Relay Control | Q1, Q2 | 2 | BC33716BU | NPN relay-driver transistor | TO-92 THT | Low-side relay coil drivers |
| Speaker Relay Control | D_RLY1, D_RLY2 | 2 | 1N4007 | Flyback diode across relay coil | Axial THT diode | Cathode toward +12 V |
| Speaker Relay Control | R_BASE1, R_BASE2 | 2 | 1 kΩ / 1% | BC337 base resistor | Axial THT | One per relay driver |
| Speaker Relay Control | R_PD1, R_PD2 | 2 | 10 kΩ / 1% | BC337 base pull-down resistor | Axial THT | Keeps relays OFF during reset/startup |
| DC Offset Detection | R_IN_L, R_IN_R | 2 | 150 kΩ / 1% | Amplifier-output attenuation resistor | Axial THT | Final DC-sensing value; one per channel |
| DC Offset Detection | R_BIAS_TOP_L/R | 2 | 10 kΩ / 1% | Upper 3.3 V ADC bias resistor | Axial THT | One per channel |
| DC Offset Detection | R_BIAS_BOT_L/R | 2 | 10 kΩ / 1% | Lower ADC bias resistor to GND | Axial THT | One per channel |
| DC Offset Detection | R_ADC_L, R_ADC_R | 2 | 4.7 kΩ | Series current-limiting resistor into STM32 ADC | Axial THT | One per channel |
| DC Offset Detection | C_DC_L, C_DC_R | 2 | 4.7 µF | Main low-pass capacitor for DC sensing | Radial THT | Final value; positive lead toward biased ADC node if electrolytic |
| DC Offset Detection | C_HF_L, C_HF_R | 2 | 100 nF / 50 V | Optional high-frequency bypass across DC-sense filter | Leaded ceramic THT | Optional but recommended |
| DC Offset Detection | D_CLAMP_L1/L2, D_CLAMP_R1/R2 | 4 | 1N5817 | Schottky ADC clamp diode | Axial THT diode | Two clamp diodes per channel |
| Temperature Monitoring | NTC1, NTC2 | 2 | B57703M0103A047 / 10 kΩ NTC | Ring-terminal thermistor for heatsink monitoring | Ring-terminal sensor | One per amplifier heatsink |
| Temperature Monitoring | R_TEMP1, R_TEMP2 | 2 | 10 kΩ / 1% | Fixed resistor for NTC divider | Axial THT | One per temperature channel |
| Temperature Monitoring | C_TEMP1, C_TEMP2 | 2 | 100 nF / 50 V | Temperature-sense filtering capacitor | Leaded ceramic THT | One per temperature channel |
| Status Indicators | LED_TEMP1, LED_TEMP2, LED_DC | 3 | Red 5 mm LED | Temperature-sensor fault and DC-fault indicators | 5 mm THT LED | Three red fault indicators |
| Status Indicators | LED_WAIT | 1 | Yellow 5 mm LED | Startup delay / speakers disconnected indicator | 5 mm THT LED | WAIT / DELAY indicator |
| Status Indicators | LED_OVERHEAT | 1 | Red or amber 5 mm LED | Overtemperature fault indicator | 5 mm THT LED | Added overtemperature indication |
| Status Indicators | R_LED1–R_LED5 | 5 | 470 Ω | LED current-limiting resistor | Axial THT | One resistor per status LED |
| Controller Connections | J_NUCLEO_A, J_NUCLEO_B | 2 | 15-pin 2.54 mm female socket | Removable NUCLEO-G031K8 connection | 2.54 mm THT socket strip | SSW-115-01-T-S or equivalent |
| Controller Connections | J1–J7 | 7 | 2-pin 5.08 mm screw terminal | External wiring connections | THT terminal block | For amplifier sense, relays, sensors and supply wiring |
| Protection Controller Power Supply | T1 | 1 | FS24-250-C2 | 230 VAC to 12 VAC isolated PCB transformer, 6 VA | PCB transformer | Dual secondary used in correct parallel phase for 12 VAC |
| Protection Controller Power Supply | BR1 | 1 | W04G-E4/51 | 1.5 A / 400 V bridge rectifier | THT bridge rectifier | Protection-controller low-voltage supply |
| Protection Controller Power Supply | C_BULK | 1 | 2200 µF / 25 V | Main rectified-DC smoothing capacitor | Radial electrolytic THT | Before 12 V regulator |
| Protection Controller Power Supply | U_REG | 1 | L7812CV | 12 V linear voltage regulator | TO-220 THT | Supplies relays and Nucleo VIN |
| Protection Controller Power Supply | C_OUT | 1 | 100 µF / 25 V | 12 V rail output smoothing capacitor | Radial electrolytic THT | After regulator |
| Protection Controller Power Supply | C_PSU1–C_PSU3 | 3 | 100 nF / 50 V | Regulator / supply bypass capacitors | Leaded ceramic THT | Local supply decoupling |
