<div align="center">

# Hi‑Fi Class‑AB Power Amplifier

### Stereo discrete power amplifier with dual 500 VA supplies, STM32 speaker protection, thermal monitoring, KiCad hardware, firmware, and measured prototype validation

**KiCad · Discrete Class‑AB · ≈±34.5 V Idle Rails · STM32G031K8 · Speaker Protection · Thermal Monitoring**

![KiCad](https://img.shields.io/badge/EDA-KiCad-314CB0?style=flat-square)
![Topology](https://img.shields.io/badge/Topology-Class--AB-444444?style=flat-square)
![MCU](https://img.shields.io/badge/MCU-STM32G031K8-03234B?style=flat-square)
![Supply](https://img.shields.io/badge/Measured%20Idle%20Rails-%C2%B134.5%20V-555555?style=flat-square)

</div>

---

## Overview

This repository contains the design, implementation, firmware, fabrication files, and measured validation of a two-channel discrete **Hi‑Fi Class‑AB power amplifier** developed in **KiCad**.

The power-amplifier stage is based on the design principles of **Rod Elliott's Elliott Sound Products (ESP) Project 3A**. This implementation expands that reference design into a complete stereo amplifier system with:

- one dedicated **500 VA transformer per audio channel**;
- independent high-current rectification and filtering for the left and right channels;
- custom amplifier and power-supply PCBs;
- **MJL21193G / MJL21194G** complementary output devices;
- a dedicated **STM32G031K8 speaker-protection controller**;
- independent left/right DC monitoring;
- dual heatsink-temperature monitoring;
- relay-controlled speaker outputs;
- firmware for startup delay, fault handling, thermal protection, and status indication;
- measured electrical validation of the completed prototype.

The repository is intended to document the project from schematic design and PCB layout through assembly, firmware, bring-up, and bench testing.

---

## Project Status

The amplifier has progressed beyond the design-only stage.

Current status:

- amplifier PCBs assembled;
- power-supply hardware assembled;
- dual-transformer stereo supply implemented;
- STM32 protection system programmed and tested;
- left and right amplifier channels operational;
- speaker relays and protection functions tested;
- DC operating points measured;
- quiescent bias measured cold and warm;
- rail voltages measured at idle and under 8 Ω load;
- rail ripple measured under load;
- frequency-response checks completed;
- upper −3 dB point measured;
- final bench-test results recorded.

The project should therefore be described as a **built and functionally validated prototype**, not only as a planned or fabrication-ready design.

---

## Table of Contents

- [Key Features](#key-features)
- [Technical Summary](#technical-summary)
- [Measured Performance](#measured-performance)
- [System Architecture](#system-architecture)
- [Power Amplifier](#power-amplifier)
- [Power Supply](#power-supply)
- [STM32 Protection Controller](#stm32-protection-controller)
- [Protection Logic](#protection-logic)
- [Thermal Management](#thermal-management)
- [PCB Design Strategy](#pcb-design-strategy)
- [Grounding Strategy](#grounding-strategy)
- [Major Components](#major-components)
- [Test Equipment](#test-equipment)
- [Repository Structure](#repository-structure)
- [Manufacturing Files](#manufacturing-files)
- [Bring-Up and Validation](#bring-up-and-validation)
- [Measurement Limitations](#measurement-limitations)
- [Safety](#safety)
- [Design Tools](#design-tools)
- [Reference Design and Credits](#reference-design-and-credits)
- [Author](#author)

---

## Key Features

### Audio Power Stage

- Two-channel discrete **Class‑AB** architecture
- One amplifier PCB per channel
- Complementary bipolar output stage
- **MJL21193G / MJL21194G** complementary output transistor pair
- **BD139 / BD140** driver stage
- **0.33 Ω / 5 W** emitter resistors
- Through-hole power devices for serviceability and heatsink mounting
- Dedicated external heatsink for each amplifier channel
- On-board **3 A** positive- and negative-rail fuses

### Main Power Supply

- **2 × 500 VA transformers**
- One transformer dedicated to the **left channel**
- One transformer dedicated to the **right channel**
- Nominal dual low-voltage secondary windings
- Measured transformer secondary voltages of approximately **25.5–25.7 VRMS per half-secondary**
- High-current bridge rectification
- **KBPC3506WP** bridge rectifier in the power-supply design
- Four **4700 µF** reservoir capacitors on the power-supply schematic
- Measured idle rails of approximately **+34.5 V / −34.5 V**
- Measured loaded rails of approximately **±33.5 to ±33.7 V** with an 8 Ω load

### Protection and Monitoring

- **ST NUCLEO‑G031K8**
- **STM32G031K8** microcontroller
- Independent left/right amplifier-output monitoring
- Independent left/right heatsink-temperature monitoring
- 10 kΩ NTC thermistors
- Startup speaker delay
- Persistent-DC fault detection
- Overtemperature shutdown
- Sensor-fault handling
- Latched fault handling and reset
- Relay-controlled left/right speaker outputs
- Front-panel status indication

### Mechanical and Thermal Design

- Large external heatsinks
- Passive natural-convection cooling
- Power transistors positioned near PCB edges for heatsink mounting
- Electrical insulation between power-transistor tabs and heatsink where required
- Metal-chassis integration
- Star-ground implementation
- Chassis protective-earth bonding
- High-current speaker and supply wiring separated from low-level input wiring

---

## Technical Summary

| Parameter | Final implementation |
|---|---|
| Amplifier topology | Discrete Class‑AB |
| Number of channels | 2 |
| Main transformers | **2 × 500 VA**, one per channel |
| Measured secondary voltage | ≈25.5–25.7 VRMS from each outer secondary lead to center tap |
| Measured idle rails | ≈+34.5 V / −34.5 V |
| Measured rails under 8 Ω test load | ≈±33.5 to ±33.7 V |
| Output devices | **MJL21194G (NPN) / MJL21193G (PNP)** |
| Output-device package | **TO‑264, through-hole** |
| Driver devices | **BD139 / BD140** |
| Output emitter resistors | **R13 / R14 = 0.33 Ω, 5 W** |
| Amplifier rail fuses | **3 A** |
| Protection controller | ST NUCLEO‑G031K8 |
| MCU | STM32G031K8 |
| Speaker relays | 2 × Omron G2RL‑1A‑E‑DC12 |
| Relay driver | BC337 NPN |
| Temperature sensing | 2 × 10 kΩ NTC |
| Cooling | External heatsinks, passive natural convection |
| Audio inputs | RCA |
| Speaker outputs | Chassis-mounted binding terminals |
| PCB CAD | KiCad |

---

# Measured Performance

The following values were measured on the completed prototype. They are reported as **bench-test results**, not as guaranteed production specifications.

## Transformer Secondary Voltages

Measured from each AC secondary lead to the center tap:

| Measurement | Left | Right |
|---|---:|---:|
| AC1 → center tap | 25.652 VRMS | 25.628 VRMS |
| AC2 → center tap | 25.631 VRMS | 25.516 VRMS |

The measurements show good agreement between the two transformer channels.

## DC Supply Rails

### Idle

| Rail | Left | Right |
|---|---:|---:|
| Positive | +34.521 V | +34.566 V |
| Negative | −34.532 V | −34.522 V |

### Under 8 Ω Amplifier Load

| Rail | Left | Right |
|---|---:|---:|
| Positive | +33.534 V | +33.678 V |
| Negative | −33.560 V | −33.701 V |

The measured rail reduction under the recorded load condition is approximately 0.8–1.0 V compared with idle.

## Rail Ripple Under 8 Ω Load

Recorded ripple values:

| Rail | Left | Right |
|---|---:|---:|
| Positive rail | 1.5 V | 1.4 V |
| Negative rail | 1.6 V | 1.4 V |

These values are reproduced as recorded in the measurement log. They should not be interpreted as a different RMS or peak-to-peak quantity unless the oscilloscope measurement mode used during the test is also specified.

## Quiescent Bias

Bias was measured as the voltage across **R13 + R14**.

Because each emitter resistor is **0.33 Ω**, the combined resistance is **0.66 Ω**.

| Channel | Cold voltage | Approx. cold current | Warm voltage | Approx. warm current |
|---|---:|---:|---:|---:|
| Left | 41.700 mV | 63.2 mA | 52.55 mV | 79.6 mA |
| Right | 41.730 mV | 63.2 mA | 55.71 mV | 84.4 mA |

The increase from cold to warm operation is documented so that bias thermal behaviour remains traceable.

## DC Output Offset

Initial recorded DC-offset measurements:

| Channel | DC offset |
|---|---:|
| Left | −54.54 mV |
| Right | −28.203 mV |

A later no-signal measurement recorded:

| Channel | Amplifier output |
|---|---:|
| Left | +42.300 mV |
| Right | −23.764 mV |

Because these measurements were taken at different points in the test sequence, they are retained separately rather than combined into a single nominal value.

## Frequency Response and Voltage Gain

With:

- input signal: **1.2 V peak-to-peak**;
- sine-wave test;
- test frequencies: **20 Hz, 50 Hz, 100 Hz, 500 Hz, 1 kHz, 5 kHz, 10 kHz, 20 kHz**;

the recorded output was approximately:

- Left: **22.6 V peak-to-peak**
- Right: **22.6 V peak-to-peak**

This corresponds to:

- voltage gain: **18.83 V/V**
- voltage gain: **25.50 dB**

No significant amplitude reduction was recorded over the tested **20 Hz to 20 kHz** audio band.

The recorded **upper −3 dB frequency** is approximately:

**250 kHz**

The protection controller may interpret very-low-frequency content below approximately **15 Hz** as a DC-like condition. This is a **protection-system behaviour**, not the amplifier's measured low-frequency −3 dB cutoff.

## 8 Ω Loaded Signal Test

With an **8 Ω load** and **Vin = 1.2 V peak-to-peak**:

| Channel | Vout | Gain V/V | Gain dB | Approx. power into 8 Ω |
|---|---:|---:|---:|---:|
| Left | 27.2 Vpp | 22.67 | 27.11 dB | 11.56 W |
| Right | 26.6 Vpp | 22.17 | 26.91 dB | 11.06 W |

The right-channel gain is **26.91 dB** from the recorded 26.6 Vpp / 1.2 Vpp values.

This test point is **not** the maximum unclipped output-power rating of the amplifier. It only documents the specific load and signal level used during that measurement.

## Protection-System Measurements

Healthy amplifier outputs produced the following DC-sense ADC voltages:

| Channel | ADC sense voltage |
|---|---:|
| Left | 1.6014 V |
| Right | 1.5969 V |

Relay-driver base voltage with relays ON:

| Channel | Base voltage |
|---|---:|
| Left | 3.2932 V |
| Right | 3.2931 V |

Relay-coil voltage with relays ON:

| Channel | Coil voltage |
|---|---:|
| Left | 11.723 V |
| Right | 11.735 V |

NTC room-temperature readings:

| Sensor | Voltage |
|---|---:|
| NTC 1 | 1.1230 V |
| NTC 2 | 1.1225 V |

The remaining protection-system functional tests were recorded as **passed**.

---

## System Architecture

The complete amplifier is divided into three main functional paths:

1. **Audio path**
2. **Power path**
3. **Protection path**

### Audio Path

```text
RCA INPUT
    │
    ▼
┌───────────────────────┐
│  Discrete Class‑AB    │
│  Power Amplifier      │
│                       │
│  • Input stage        │
│  • Voltage gain stage │
│  • Bias network       │
│  • Driver stage       │
│  • Output stage       │
└───────────┬───────────┘
            │
            ▼
┌───────────────────────┐
│  Speaker Protection   │
│  Relay                │
└───────────┬───────────┘
            │
            ▼
       SPEAKER OUT
```

### Power Path

```text
                         230 VAC MAINS
                               │
               ┌───────────────┴───────────────┐
               ▼                               ▼
      500 VA TRANSFORMER #1           500 VA TRANSFORMER #2
           LEFT CHANNEL                    RIGHT CHANNEL
               │                               │
               ▼                               ▼
       RECTIFIER + FILTER              RECTIFIER + FILTER
               │                               │
               ▼                               ▼
        LEFT ±34 V RAILS                RIGHT ±34 V RAILS
               │                               │
               ▼                               ▼
        LEFT AMPLIFIER                  RIGHT AMPLIFIER
```

Each channel therefore has its own transformer and power-supply path, reducing shared supply impedance between the two amplifier channels.

### Protection Path

```text
Left Amp Output  ─────► DC Sense ───────┐
Right Amp Output ─────► DC Sense ───────┤
Left Heatsink NTC ────► Temp Sense ─────┤
Right Heatsink NTC ───► Temp Sense ─────┤
                                         ▼
                              ┌────────────────────┐
                              │   STM32G031K8      │
                              │                    │
                              │ • ADC acquisition  │
                              │ • Startup delay    │
                              │ • Fault logic      │
                              │ • Thermal logic    │
                              └─────────┬──────────┘
                                        │
                                  Relay drivers
                                        │
                                  ┌─────┴─────┐
                                  ▼           ▼
                              Left relay  Right relay
                                  │           │
                                  ▼           ▼
                              Left spk.   Right spk.
```

---

## Power Amplifier

The audio section uses a conventional **discrete Class‑AB power-amplifier topology** based on the principles of ESP Project 3A.

Functional stages include:

1. **Input stage** — accepts the low-level audio signal.
2. **Voltage-amplification stage** — provides the main voltage gain.
3. **Bias network** — establishes Class‑AB idle current.
4. **Driver stage** — provides base drive for the power output devices.
5. **Complementary output stage** — supplies current to the loudspeaker.

### Output Devices

| Reference | Device | Polarity | Package |
|---|---|---|---|
| Q7 | **MJL21193G** | PNP | TO‑264 |
| Q8 | **MJL21194G** | NPN | TO‑264 |

The output devices are mounted close to the PCB edge so that they can be attached directly to the external heatsink.

Electrical isolation hardware and thermal-interface material must be used where required by the mechanical installation.

### Driver Stage

The amplifier uses complementary **BD139 / BD140** driver transistors.

### Output Emitter Resistors

- **R13 = 0.33 Ω / 5 W**
- **R14 = 0.33 Ω / 5 W**

These resistors are also used as convenient measurement points for the output-stage quiescent current.

### Rail Protection

Each amplifier board includes:

- **3 A fuse in the positive rail**
- **3 A fuse in the negative rail**

These fuses protect the amplifier board but do not replace the required mains-side transformer protection.

---

## Power Supply

The final stereo implementation uses a **dual-mono-style power architecture**:

- one **500 VA transformer** for the left channel;
- one **500 VA transformer** for the right channel.

Each transformer has a center-tapped secondary arrangement and feeds its own rectifier/filter path.

Measured secondary voltages are approximately **25.5–25.7 VRMS from each outer secondary lead to the center tap**.

After rectification and reservoir filtering, the measured idle rails are approximately:

```text
+34.5 V
  0 V
−34.5 V
```

Under the recorded 8 Ω load test, the rails remained approximately **±33.5 to ±33.7 V**.

### Rectification and Filtering

The power-supply schematic uses:

- **Diotec KBPC3506WP** bridge rectifier;
- four **4700 µF** reservoir capacitors;
- local bypass capacitors;
- heavy-current connections for the DC rails and common return.

### Power-Supply Design Priorities

- short transformer-to-rectifier wiring;
- short rectifier-to-reservoir-capacitor paths;
- adequate conductor cross-section;
- deliberate star grounding;
- high-current speaker returns separated from input ground;
- secure protective-earth bonding;
- mains-rated switchgear, wiring, insulation, and fuse protection;
- independent left/right channel supply paths.

---

## STM32 Protection Controller

Speaker protection is implemented with an **ST NUCLEO‑G031K8** carrying the **STM32G031K8** microcontroller.

The controller supervises both amplifier channels and only connects the loudspeakers when the monitored conditions are safe.

### ADC Inputs

The controller monitors:

| Signal | MCU pin / ADC input |
|---|---|
| TEMP1 | PA0 / A0 |
| TEMP2 | PA1 / A1 |
| DC_LEFT | PA4 / A2 |
| DC_RIGHT | PA5 / A3 |

The firmware uses ADC averaging to improve measurement stability.

### Protection Timing and Thermal Thresholds

Current firmware configuration includes:

- startup delay: **3 s**
- periodic protection sampling
- overtemperature trip: approximately **100 °C**
- thermal reset threshold: approximately **90 °C**
- latched fault handling where applicable
- manual fault-reset support

### Controlled Outputs

The controller operates:

- left speaker relay;
- right speaker relay;
- status and fault LEDs;
- relay drivers through BC337 transistors.

---

## Protection Logic

### Startup Delay

At power-up, the loudspeakers remain disconnected while the MCU initializes and checks the monitored conditions.

```text
POWER ON
   │
   ▼
MCU INITIALIZATION
   │
   ▼
ADC + GPIO INITIALIZATION
   │
   ▼
VERIFY SENSOR / DC CONDITIONS
   │
   ▼
3 s STARTUP DELAY
   │
   ▼
ENABLE SPEAKER RELAYS
```

If a fault exists, the speaker relays remain disabled.

### DC Protection

The left and right amplifier outputs are independently monitored through conditioned ADC inputs.

A persistent abnormal positive or negative DC component causes the controller to disable the associated speaker connection.

```text
ABNORMAL DC
     │
     ▼
STM32 FAULT DECISION
     │
     ▼
RELAY DRIVER OFF
     │
     ▼
SPEAKER DISCONNECTED
```

The healthy operating point of the DC-sense channels is approximately **1.6 V**, allowing the circuit to detect excursions in either direction.

### Very-Low-Frequency Behaviour

The implemented protection logic may classify signals below approximately **15 Hz** as DC-like.

This should not be confused with the amplifier's audio-band frequency response.

### Temperature Protection

Each channel uses a **10 kΩ NTC thermistor** attached to the thermal system.

```text
LEFT HEATSINK  ──► NTC ──► ADC
RIGHT HEATSINK ──► NTC ──► ADC
```

The controller can disconnect the loudspeakers when the thermal trip threshold is reached.

### Relay Drive

The STM32 does not energize the relay coils directly.

Each channel uses:

```text
STM32 GPIO
    │
    ▼
Base resistor
    │
    ▼
BC337 NPN
    │
    ▼
12 V relay coil
    │
    └── Flyback diode
```

Measured relay-coil voltage in the ON state is approximately **11.7 V**.

### Speaker Relays

Two **Omron G2RL‑1A‑E‑DC12** relays are used:

- one for the left channel;
- one for the right channel.

---

## Thermal Management

The amplifier is designed for passive cooling using external chassis heatsinks.

The thermal design includes:

- one external heatsink per amplifier channel;
- direct mounting of the TO‑264 power transistors;
- electrical insulation where required;
- thermal compound / thermal interface material;
- NTC sensing;
- firmware-based overtemperature protection;
- natural-convection airflow;
- no fan dependency.

The output-stage bias was measured both cold and after thermal stabilization to document thermal drift.

---

## PCB Design Strategy

The PCB layout was developed with audio performance, current handling, serviceability, and manufacturability in mind.

### High-Current Paths

High-current paths include:

- rectifier connections;
- reservoir-capacitor charging loops;
- ± rail distribution;
- output-stage supply paths;
- speaker-output routing;
- speaker-return current;
- relay contacts.

These paths should be kept short and wide.

### Small-Signal Paths

Sensitive nodes include:

- RCA input;
- input-stage circuitry;
- feedback network;
- bias-related nodes;
- low-level signal ground.

These are kept away from rectifier, relay-coil, transformer, and speaker-current paths as much as practical.

### Serviceability

Through-hole components are used extensively so that stressed devices, connectors, relays, drivers, and power transistors can be replaced during repair or development.

---

## Grounding Strategy

The final system uses a deliberate **star-ground approach**.

Both transformer center taps are brought to the central high-current ground reference, together with the appropriate power-supply returns.

The grounding strategy distinguishes between:

```text
SENSITIVE SIGNAL GROUND
         │
         ▼
CENTRAL / STAR REFERENCE
         ▲
         │
HIGH-CURRENT POWER GROUND
```

Design goals:

- prevent rectifier charging current from flowing through input-signal ground;
- keep feedback references electrically quiet;
- keep speaker return as a high-current path;
- avoid long shared ground traces;
- minimize hum and channel interaction;
- keep protection-controller current from disturbing the analog signal reference.

The metal chassis protective earth is treated separately from the audio star-ground function and must remain securely bonded for safety.

---

## Major Components

| Function | Selected component / specification |
|---|---|
| NPN output transistor | **MJL21194G** |
| PNP output transistor | **MJL21193G** |
| Driver transistors | **BD139 / BD140** |
| Output emitter resistors | **0.33 Ω / 5 W** |
| Amplifier rail fuses | **3 A** |
| Main transformers | **2 × 500 VA**, one per channel |
| Main bridge rectifier | **Diotec KBPC3506WP** |
| Reservoir capacitors | **4 × 4700 µF** on the power-supply schematic |
| Protection development board | **ST NUCLEO‑G031K8** |
| MCU | **STM32G031K8** |
| Speaker relays | **Omron G2RL‑1A‑E‑DC12** |
| Relay driver | **BC337** |
| Temperature sensors | **10 kΩ NTC** |
| Audio input | RCA |
| Speaker output | Chassis-mounted binding terminals |
| Cooling | External passive heatsinks |

---

## Test Equipment

The completed amplifier was tested using the following bench instruments:

| Instrument | Model | Use |
|---|---|---|
| Oscilloscope | **UNI‑T UPO1202** | Waveform, amplitude, ripple, frequency-response and output measurements |
| Function / signal generator | **OWON DGE1030** | Sine-wave test-signal generation |
| Digital multimeter | **OWON XDM2041** | DC rails, bias, offsets, relay voltages, sensor voltages and continuity checks |

Measurement results in this README should be interpreted together with the stated load, signal amplitude, and test condition.

---

## Repository Structure

```text
Power-Amplifier/
│
├── Firmware/
│   └── STM32/
│
├── Images/
│
├── KiCad/
│
├── Libraries/
│
├── Manufacturing/
│
├── PDF/
│
├── Schematics/
│
└── README.md
```

### Directory Overview

| Path | Contents |
|---|---|
| `Firmware/STM32/` | STM32 source, configuration, project files, and protection-controller firmware |
| `Images/` | Project photographs, PCB renders, diagrams, and screenshots |
| `KiCad/` | Editable KiCad schematic and PCB project files |
| `Libraries/` | Project-specific KiCad symbols and footprints |
| `Manufacturing/` | Gerber and drill outputs for PCB fabrication |
| `PDF/` | PDF exports and project documentation |
| `Schematics/` | Exported schematic drawings |
| `README.md` | Main project overview and measured validation summary |

---

## Manufacturing Files

The fabrication package contains the files required by a typical PCB manufacturer.

### Gerber Outputs

Typical exported layers include:

- copper;
- solder mask;
- silkscreen;
- board outline / `Edge.Cuts`;
- other fabrication layers required by the board.

### Drill Outputs

The project distinguishes between:

- **PTH** — plated through holes;
- **NPTH** — non-plated mechanical holes, where present.

Gerber files and drill files are both required for a complete PCB manufacturing package.

---

## Bring-Up and Validation

The completed hardware was commissioned using a staged validation procedure.

### 1. Visual and Assembly Inspection

- verify transistor orientation and pinout;
- verify MJL21193G / MJL21194G mounting;
- verify insulation from heatsink where required;
- verify electrolytic polarity;
- verify diode and relay orientation;
- inspect solder joints and high-current connections.

### 2. Unpowered Electrical Checks

- continuity;
- rail-to-ground short checks;
- transistor junction checks;
- ground-path verification;
- output-stage connection verification.

### 3. Power-Supply Validation

- verify transformer secondaries;
- verify bridge-rectifier polarity;
- measure positive and negative rails;
- compare left and right channels;
- measure rail behaviour under load.

### 4. Controlled Amplifier Power-Up

- loudspeakers disconnected initially;
- monitor DC offset;
- monitor bias voltage;
- monitor transistor temperature;
- verify no uncontrolled rail current.

### 5. Protection Validation

- startup delay;
- DC monitoring;
- relay operation;
- NTC sensing;
- thermal handling;
- sensor-fault behaviour;
- fault indication;
- reset behaviour.

### 6. Signal Validation

- apply a known sine-wave input;
- observe the amplifier output on the oscilloscope;
- test with a suitable resistive load;
- verify operation across the audio-frequency range;
- progressively increase signal level while monitoring rails and temperature.

---

## Measurement Limitations

The current measurement set documents successful functional operation and several important electrical characteristics.

The following values have **not** been established as formal amplifier specifications and should not be claimed without additional controlled measurements:

- THD / THD+N;
- signal-to-noise ratio;
- channel separation / crosstalk;
- maximum continuous output power;
- maximum unclipped output voltage at clipping;
- full thermal-rise curve versus continuous output power;
- damping factor;
- slew rate.

Because no additional measurements are currently available, this README reports only the values that were actually recorded or that can be directly calculated from those recorded values.

---

## Safety

> This project interfaces with **230 VAC mains voltage** and contains high-current circuitry and large energy-storage capacitors. Incorrect construction or testing can cause electric shock, fire, equipment damage, or component failure.

Important safety requirements include:

- correctly rated mains fuse protection;
- protective-earth bonding to the metal chassis;
- mains-rated switch and wiring;
- suitable insulation;
- correct conductor cross-section;
- strain relief;
- secure transformer mounting;
- adequate creepage and clearance;
- insulated exposed mains connections;
- safe transistor/heatsink insulation;
- awareness that reservoir capacitors retain stored energy after shutdown.

**Never service, modify, or probe the mains section while the unit is energized.**

---

## Design Tools

| Tool / source | Purpose |
|---|---|
| **KiCad** | Schematic capture, PCB design, footprints, and fabrication outputs |
| **STM32CubeMX** | STM32 peripheral and project configuration |
| **STM32CubeIDE** | STM32 firmware development, programming, and debugging |
| **Mouser Electronics** | Component sourcing |
| **Manufacturer datasheets** | Electrical, thermal, package, and footprint verification |
| **Git / GitHub** | Version control and repository documentation |

---

## Reference Design and Credits

The core amplifier topology is based on:

**Rod Elliott — Elliott Sound Products (ESP), Project 3A Power Amplifier**

Reference:

https://sound-au.com/project3a.htm

Credit for the original amplifier topology belongs to **Rod Elliott / Elliott Sound Products**.

This repository documents the project-specific implementation around that topology, including:

- PCB implementation;
- component selection;
- dual 500 VA transformer architecture;
- power-supply integration;
- STM32 protection controller;
- DC monitoring;
- temperature monitoring;
- relay control;
- firmware;
- grounding;
- chassis integration;
- fabrication files;
- prototype assembly;
- measured validation.

---

## Engineering Goals

The project was developed around the following objectives:

- reliable discrete Class‑AB amplification;
- independent left/right power delivery;
- speaker protection against persistent DC;
- temperature monitoring and shutdown;
- low-noise PCB layout;
- deliberate grounding;
- practical current handling;
- serviceable construction;
- sourceable components;
- reproducible PCB fabrication;
- embedded protection firmware;
- measured bench validation;
- clear engineering documentation.

---

## Author

**Stamatis Mavitzis**  
Electrical & Computer Engineering

Designed in **KiCad**.

---

<div align="center">

### Hi‑Fi Power Amplifier · Engineering Project

*Discrete Class‑AB audio amplification, dual 500 VA power supplies, STM32 protection, PCB design, firmware, manufacturing files, and measured prototype validation.*

</div>
