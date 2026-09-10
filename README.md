<div align="center">

# Hi‑Fi Class‑AB Power Amplifier

### Discrete stereo power amplifier with STM32-based speaker protection, thermal monitoring, and production-ready KiCad files

**KiCad · Discrete Class‑AB · ±32 V Rails · STM32G031K8 · Speaker Protection · Thermal Monitoring**

![KiCad](https://img.shields.io/badge/EDA-KiCad-314CB0?style=flat-square)
![Topology](https://img.shields.io/badge/Topology-Class--AB-444444?style=flat-square)
![MCU](https://img.shields.io/badge/MCU-STM32G031K8-03234B?style=flat-square)
![Supply](https://img.shields.io/badge/Main%20Rails-%C2%B132%20V-555555?style=flat-square)
![Hardware](https://img.shields.io/badge/Hardware%20Design-Complete-success?style=flat-square)
![Testing](https://img.shields.io/badge/Hardware%20Validation-Pending-orange?style=flat-square)

</div>

---

## Overview

This repository contains the complete hardware design of a **two-channel discrete Hi‑Fi Class‑AB power amplifier** developed in **KiCad**.

The amplifier stage is based on the design principles of **Rod Elliott's ESP Project 3A**, while the complete implementation extends the reference concept with a custom PCB, power-supply integration, modern component selection, thermal management, and a dedicated **STM32-based speaker protection controller**.

The project covers the complete hardware workflow from schematic capture to manufacturing output:

- amplifier and power-supply schematics;
- STM32 protection and monitoring circuitry;
- PCB layout and grounding strategy;
- component and footprint selection;
- thermal and mechanical integration;
- bill of materials;
- Gerber and drill generation;
- documentation for fabrication, assembly, and later validation.

> **Current status:** the electrical and PCB design is complete. Physical fabrication, firmware completion, first power-up, calibration, and measured audio-performance characterization are the next stages.

---

## Table of Contents

- [Key Features](#key-features)
- [Technical Summary](#technical-summary)
- [System Architecture](#system-architecture)
- [Power Amplifier](#power-amplifier)
- [Power Supply](#power-supply)
- [STM32 Protection Controller](#stm32-protection-controller)
- [Protection Logic](#protection-logic)
- [Thermal Management](#thermal-management)
- [PCB Design Strategy](#pcb-design-strategy)
- [Grounding Strategy](#grounding-strategy)
- [Major Components](#major-components)
- [Repository Structure](#repository-structure)
- [Schematics and Documentation](#schematics-and-documentation)
- [Manufacturing Files](#manufacturing-files)
- [Bill of Materials](#bill-of-materials)
- [Mechanical Integration](#mechanical-integration)
- [Bring-Up and Validation Plan](#bring-up-and-validation-plan)
- [Safety](#safety)
- [Design Tools](#design-tools)
- [Project Status](#project-status)
- [Reference Design and Credits](#reference-design-and-credits)
- [Author](#author)

---

## Key Features

### Audio Power Stage

- Two-channel discrete **Class‑AB** architecture
- Complementary bipolar output stage
- Toshiba **2SC5200‑O / 2SA1943‑O** output transistor pair
- Through-hole power devices for serviceability and heatsink mounting
- Short high-current output paths
- Dedicated external heatsinking for each amplifier channel

### Main Power Supply

- Approximately **±32 V DC** amplifier supply rails
- **25‑0‑25 VAC / 300 VA** toroidal transformer
- High-current bridge rectification
- Large reservoir/filter capacitors
- Separate consideration of high-current charging paths and small-signal grounding

### Protection and Monitoring

- **ST NUCLEO‑G031K8**
- **STM32G031K8** microcontroller
- Independent left/right DC-output monitoring
- Independent left/right heatsink temperature monitoring
- 10 kΩ NTC thermistors
- Startup speaker-delay logic
- Automatic speaker disconnection under fault conditions
- Overtemperature shutdown
- Relay-controlled left/right speaker outputs
- Front-panel status indication

### Mechanical and Thermal Design

- Large external heatsinks
- Power transistors positioned near PCB edges for practical mounting
- Four AC cooling fans
- PCB mounting holes and enclosure integration
- High-current spade and terminal connections where appropriate

---

## Technical Summary

| Parameter | Design |
|---|---|
| Amplifier topology | Discrete Class‑AB |
| Number of channels | 2 |
| Main DC rails | Approximately ±32 V |
| Main transformer | 25‑0‑25 VAC, 300 VA toroidal |
| Output devices | 2SC5200‑O / 2SA1943‑O |
| Output-device package | TO‑3P(L), through-hole |
| Protection controller | ST NUCLEO‑G031K8 |
| MCU | STM32G031K8 |
| Speaker relays | 2 × Omron G2RL‑1A‑E‑DC12 |
| Relay driver | BC337 NPN |
| Temperature sensing | 2 × 10 kΩ NTC |
| Cooling | 2 external heatsinks + 4 AC fans |
| Audio inputs | RCA |
| Speaker outputs | Gold-plated binding terminals |
| PCB CAD | KiCad |
| Hardware design state | Complete |
| Fabrication / measured validation | Pending |

### Performance Data

Electrical performance will be published after the physical amplifier has been assembled and tested.

The following values are therefore **not claimed at this stage**:

- continuous output power;
- total harmonic distortion (THD);
- frequency response;
- signal-to-noise ratio;
- DC offset;
- thermal rise under sustained load;
- protection trip thresholds and timing accuracy.

Keeping simulated/design intent separate from measured hardware results makes the repository more technically rigorous and reproducible.

---

## System Architecture

The design is divided into the **audio path**, **power path**, and **protection path**.

```text
                         AUDIO PATH

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

```text
                         POWER PATH

          25‑0‑25 VAC / 300 VA
          TOROIDAL TRANSFORMER
                   │
                   ▼
          HIGH-CURRENT RECTIFIER
                   │
                   ▼
           RESERVOIR CAPACITORS
                   │
        ┌──────────┼──────────┐
        ▼          ▼          ▼
      +32 V       GND       -32 V
        │                     │
        └────► AMPLIFIER ◄────┘
```

```text
                      PROTECTION PATH

 Left Amp Output ───────► DC Sense ───────┐
 Right Amp Output ──────► DC Sense ───────┤
 Left Heatsink NTC ─────► Temp Sense ─────┤
 Right Heatsink NTC ────► Temp Sense ─────┤
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

The audio section uses a conventional **discrete Class‑AB power-amplifier topology**.

Its functional stages include:

1. **Input stage** — receives the low-level audio signal.
2. **Voltage-amplification stage** — provides the majority of the amplifier's open-loop voltage gain.
3. **Bias network** — establishes the required Class‑AB idle operating condition.
4. **Driver stage** — supplies sufficient base current to the power output devices.
5. **Complementary output stage** — delivers current to the loudspeaker load.

The physical PCB layout is designed so that low-level input circuitry is kept away from the highest-current supply and output paths.

### Output Transistors

The final complementary output devices are:

| Device | Polarity | Package | Mounting |
|---|---|---|---|
| **2SC5200‑O** | NPN | TO‑3P(L) | Through-hole / external heatsink |
| **2SA1943‑O** | PNP | TO‑3P(L) | Through-hole / external heatsink |

The output devices are positioned near the PCB edges so that their bodies can be mechanically coupled to the amplifier heatsinks without requiring long high-current PCB traces.

Where required by the mechanical/electrical arrangement, appropriate insulating hardware must be used between transistor tabs and heatsinks.

---

## Power Supply

The main amplifier is designed around a symmetrical supply of approximately:

```text
+32 V
 GND
-32 V
```

The supply chain is:

```text
230 VAC mains
     │
     ▼
25‑0‑25 VAC toroidal transformer
     │
     ▼
High-current bridge rectifier
     │
     ▼
Reservoir / smoothing capacitors
     │
     ├────────► +V rail
     ├────────► 0 V / power ground
     └────────► -V rail
```

A **35 A bridge rectifier** is used in the high-current main supply.

Particular attention is given to the current loops created by the rectifier and reservoir capacitors. These charging currents can contain large pulses and must not share unnecessary impedance with sensitive input, feedback, or small-signal ground paths.

---

## STM32 Protection Controller

Speaker protection is handled by a dedicated controller based on the **ST NUCLEO‑G031K8**, which carries the **STM32G031K8** microcontroller.

The controller supervises both amplifier channels and determines when the loudspeakers may safely remain connected.

### Monitored Inputs

The controller receives signals from:

| Monitored quantity | Channel | MCU function |
|---|---|---|
| Amplifier DC condition | Left | ADC |
| Amplifier DC condition | Right | ADC |
| Heatsink temperature | Left | ADC |
| Heatsink temperature | Right | ADC |

### Controlled Outputs

The controller operates:

- left speaker relay;
- right speaker relay;
- status/fault LEDs;
- protection-state indication.

---

## Protection Logic

### 1. Startup Speaker Delay

At power-up, the loudspeakers remain disconnected while the controller initializes and verifies that the amplifier is in a safe state.

```text
POWER ON
   │
   ▼
MCU INITIALIZATION
   │
   ▼
CHECK DC CHANNELS
   │
   ▼
CHECK TEMPERATURE CHANNELS
   │
   ▼
STARTUP DELAY
   │
   ▼
ENABLE SPEAKER RELAYS
```

The purpose of this delay is to reduce the possibility of startup transients reaching the loudspeakers.

### 2. DC Output Protection

Each amplifier output is monitored independently.

Because the amplifier output is an AC audio signal centred around approximately 0 V, the sensing circuit conditions the signal before it reaches the STM32 ADC.

The protection firmware is intended to distinguish normal audio activity from a **persistent positive or negative DC component**.

When an unsafe DC condition is detected:

```text
ABNORMAL DC
     │
     ▼
STM32 FAULT DECISION
     │
     ▼
RELAY DRIVER DISABLED
     │
     ▼
SPEAKER DISCONNECTED
```

A persistent DC output can damage a loudspeaker voice coil, so the relay provides a physical means of isolating the speaker from the amplifier output.

### 3. Overtemperature Protection

Each heatsink is monitored using a **10 kΩ NTC thermistor**.

```text
LEFT HEATSINK  ──► NTC ──► ADC
RIGHT HEATSINK ──► NTC ──► ADC
```

The MCU evaluates the temperature channels and can disconnect the speakers if a configured thermal limit is exceeded.

The protection design also allows abnormal sensor conditions to be treated separately from a genuine overtemperature event.

### 4. Relay Drive

The STM32 does **not** drive the relay coils directly.

Each relay channel uses:

```text
STM32 GPIO
    │
    ▼
Base resistor
    │
    ▼
BC337 NPN transistor
    │
    ▼
12 V relay coil
    │
    └── Flyback diode across coil
```

The transistor supplies the relay-coil current, while the flyback diode suppresses the inductive voltage generated when the coil is switched off.

### 5. Speaker Relays

Two **Omron G2RL‑1A‑E‑DC12** relays are used:

- one for the left channel;
- one for the right channel.

Independent relays allow a fault-handling strategy in which the channels can be supervised individually.

### 6. Status Indicators

Front-panel LEDs provide visual feedback for states such as:

- startup / relay delay;
- normal operation;
- DC fault;
- temperature-sensor fault;
- overtemperature;
- active speaker protection.

This makes the protection system easier to diagnose without requiring a debugger or external test equipment.

---

## Thermal Management

Power-device temperature is a central part of the amplifier design.

The thermal system includes:

- one large external heatsink per amplifier channel;
- heatsink-mounted temperature sensing;
- STM32-based thermal protection;
- forced-air cooling;
- four AC fans;
- power-transistor placement close to PCB edges;
- mechanical clearance for transistor mounting hardware.

Thermal compound, insulators, bushings, and mounting torque should be selected according to the actual output-device and heatsink installation.

No final thermal-performance claim is made until the assembled amplifier has been tested under controlled load conditions.

---

## PCB Design Strategy

The PCB layout was developed with audio performance, current handling, thermal management, serviceability, and manufacturability in mind.

### High-Current Routing

High-current paths include:

- rectifier connections;
- reservoir-capacitor charging loops;
- ±32 V rail distribution;
- output-stage supply paths;
- speaker-output routing;
- speaker-return current;
- relay contacts and output connectors.

These paths are kept short and appropriately wide where practical.

### Small-Signal Routing

Sensitive nodes include:

- RCA input;
- input-stage circuitry;
- feedback network;
- bias-related nodes;
- low-level signal ground.

These signals are physically separated from noisy switching, rectifier, relay-coil, and high-current paths as much as possible.

### Placement Priorities

Component placement considers:

- signal-flow direction;
- short high-current loops;
- output-transistor heatsink access;
- connector accessibility;
- relay placement;
- NTC wiring;
- test access;
- mounting holes;
- enclosure clearances;
- silkscreen readability.

### Serviceability

Through-hole parts are used where appropriate so that high-power components, connectors, relays, and other stressed devices can be replaced more easily during maintenance or prototyping.

---

## Grounding Strategy

Grounding is one of the most important parts of a high-power audio design.

The layout distinguishes between the roles of:

```text
 SENSITIVE SIGNAL GROUND
          │
          ▼
 CENTRAL / STAR REFERENCE
          ▲
          │
 HIGH-CURRENT POWER GROUND
```

The objective is to prevent large rectifier, capacitor, output-stage, and loudspeaker-return currents from producing unwanted voltage drops in the ground paths used by low-level audio circuitry.

### Grounding Principles

- Keep input-signal returns away from rectifier charging currents.
- Keep feedback reference paths electrically quiet.
- Treat speaker return as a **high-current** path.
- Avoid long shared ground traces between small-signal and power sections.
- Join ground domains at intentional low-impedance points rather than accidentally through long PCB paths.
- Keep protection-controller grounding from disturbing the analog audio reference.

This approach helps reduce:

- mains hum;
- ground-loop sensitivity;
- supply-current coupling;
- unwanted noise injection;
- channel interaction through shared ground impedance.

---

## Major Components

| Function | Selected component / specification |
|---|---|
| NPN output transistor | **2SC5200‑O** |
| PNP output transistor | **2SA1943‑O** |
| Protection development board | **ST NUCLEO‑G031K8** |
| Microcontroller | **STM32G031K8** |
| Speaker relays | **Omron G2RL‑1A‑E‑DC12** |
| Relay driver transistor | **BC337** |
| Temperature sensors | **10 kΩ NTC thermistors** |
| Main transformer | **25‑0‑25 VAC, 300 VA toroidal** |
| Main rectifier | **35 A bridge rectifier** |
| Amplifier supply | **Approximately ±32 V DC** |
| Audio input | **RCA connectors** |
| Speaker output | **Gold-plated binding terminals** |
| Cooling | **2 heatsinks + 4 AC fans** |

The complete component list is maintained separately in the project BOM.

---

## Repository Structure

The repository is organized into dedicated top-level folders so that the editable design files, exported documentation, custom KiCad libraries, images, and PCB manufacturing outputs remain clearly separated.

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
| `Firmware/STM32/` | STM32 source code, configuration files, project files, and firmware documentation for the speaker-protection controller |
| `Images/` | Project photographs, PCB renders, diagrams, screenshots, and other visual material used for documentation |
| `KiCad/` | Editable KiCad project source files, including schematic and PCB design files |
| `Libraries/` | Project-specific KiCad symbols, footprints, and supporting custom-library files |
| `Manufacturing/` | PCB fabrication outputs such as Gerber and drill files |
| `PDF/` | PDF exports of project documentation and design drawings |
| `Schematics/` | Exported schematic drawings for convenient viewing without opening KiCad |
| `README.md` | Main GitHub project documentation and technical overview |

### Organization Philosophy

The repository intentionally separates **editable engineering source files** from **generated outputs**.

```text
Editable design source
        │
        ├──► KiCad/
        └──► Libraries/

Embedded firmware
        │
        └──► Firmware/STM32/

Documentation
        │
        ├──► Schematics/
        ├──► PDF/
        └──► Images/

Manufacturing output
        │
        └──► Manufacturing/
```

This organization makes the project easier to review, maintain, manufacture, and share.

A user who wants to modify the hardware can work from the `KiCad/` and `Libraries/` directories. STM32 firmware development is kept separately in `Firmware/STM32/`, while users who only want to inspect the project can use the exported files in `Schematics/`, `PDF/`, and `Images/`.

The `Manufacturing/` directory is reserved for files intended for PCB fabrication rather than editable KiCad source files.

---

## Schematics and Documentation

The design documentation is divided into the main functional blocks.

### Power Amplifier

Contains the complete discrete Class‑AB amplifier circuitry, including the signal, gain, driver, bias, and output stages.

### Main Power Supply

Contains the transformer interface, bridge rectifier, reservoir filtering, and symmetrical amplifier supply rails.

### Protection Controller

Contains:

- STM32 development-board connections;
- left/right DC sensing;
- left/right temperature sensing;
- speaker relay drivers;
- status LEDs;
- controller power-supply circuitry.

---

## Manufacturing Files

The PCB fabrication package includes the outputs required by a typical PCB manufacturer.

### Gerber Outputs

These normally include the required:

- copper layers;
- solder-mask layers;
- silkscreen layers;
- board outline / `Edge.Cuts`;
- other fabrication layers used by the final board.

### Drill Outputs

Drill data is stored together with the Gerbers when preparing a board for fabrication.

The project distinguishes between:

- **PTH** — plated through holes;
- **NPTH** — non-plated mechanical holes, where present.

> Gerbers describe the PCB layer geometry; drill files describe the holes. A complete manufacturing package normally requires both.

---

## Bill of Materials

The BOM is maintained separately from the schematic source so it can be used for sourcing and assembly.

Component selection considers:

- electrical voltage/current ratings;
- power dissipation;
- tolerance where relevant;
- transistor and diode ratings;
- physical package;
- KiCad footprint compatibility;
- through-hole mounting requirements;
- distributor availability;
- mechanical dimensions;
- thermal requirements;
- serviceability.

Distributor or manufacturer part numbers may be maintained in dedicated BOM versions without cluttering the design overview.

---

## Mechanical Integration

The project is designed as a complete amplifier assembly rather than only an isolated PCB.

Mechanical considerations include:

- PCB mounting holes;
- amplifier heatsinks;
- output-transistor mounting;
- NTC placement;
- airflow path;
- four cooling fans;
- toroidal-transformer mounting;
- front-panel status LEDs;
- RCA input connectors;
- speaker binding posts;
- mains switch;
- fuse holders;
- protective-earth connection;
- internal cable routing;
- high-current spade connections;
- service access.

Keeping the power devices near the PCB edges reduces the distance between the transistor leads, PCB, and heatsink installation.

---

## Bring-Up and Validation Plan

The amplifier has not yet reached the final measured-validation stage. A controlled bring-up sequence is therefore an important part of the project.

### Recommended Validation Sequence

1. **Visual inspection**
   - component orientation;
   - solder joints;
   - transistor pinout;
   - electrolytic capacitor polarity;
   - diode orientation;
   - connector pinout;
   - insulation and clearances.

2. **Unpowered electrical checks**
   - continuity;
   - short circuits between rails;
   - ground connectivity;
   - resistance checks around the output stage.

3. **Power-supply validation**
   - transformer secondary voltages;
   - rectified rails;
   - rail symmetry;
   - ripple;
   - controller supply.

4. **Current-limited first power-up**
   - verify that no abnormal current is drawn;
   - monitor output DC offset;
   - verify transistor temperature.

5. **Protection-system validation**
   - startup delay;
   - relay operation;
   - left/right DC fault response;
   - temperature sensing;
   - overtemperature response;
   - LED state indication.

6. **Low-level signal test**
   - inject a sine wave;
   - verify clean output waveform;
   - confirm gain and symmetry.

7. **Dummy-load testing**
   - increase output gradually;
   - monitor temperature and rail behaviour;
   - verify protection does not false-trigger.

8. **Audio characterization**
   - output power;
   - frequency response;
   - distortion;
   - noise;
   - channel consistency;
   - thermal behaviour.

Measured results should be added to this README only after the test conditions and instrumentation are documented.

---

## Safety

> [!CAUTION]
> This project interfaces with **mains voltage** and contains high-current power circuitry and large energy-storage capacitors. Incorrect construction or testing can cause electric shock, fire, equipment damage, or component failure.

Important safety requirements include:

- correctly rated mains fuse protection;
- protective-earth bonding to the metal chassis;
- suitable mains-rated switch and wiring;
- correct insulation;
- appropriate wire gauge;
- strain relief;
- transformer mounting hardware;
- adequate PCB creepage and clearance;
- insulated exposed mains connections;
- safe heatsink insulation where required;
- discharge awareness for large reservoir capacitors.

Large electrolytic capacitors may retain dangerous stored energy after power has been removed.

**Never service, modify, or probe the mains section while the unit is energized.**

---

## Design Tools

The project workflow uses:

| Tool / source | Purpose |
|---|---|
| **KiCad** | Schematic capture, PCB design, footprints, manufacturing outputs |
| **Mouser Electronics** | Component sourcing and availability checks |
| **Manufacturer datasheets** | Electrical, thermal, package, and footprint verification |
| **Git / GitHub** | Version control, repository organization, and documentation |

---

## Project Status

| Area | Status |
|---|---|
| Power-amplifier schematic | ✅ Complete |
| Main power-supply schematic | ✅ Complete |
| STM32 protection hardware | ✅ Complete |
| DC sensing circuitry | ✅ Complete |
| Temperature sensing | ✅ Complete |
| Speaker relay drivers | ✅ Complete |
| Status LED circuitry | ✅ Complete |
| Component selection | ✅ Complete |
| Footprint assignment | ✅ Complete |
| PCB layout | ✅ Complete |
| Grounding strategy | ✅ Complete |
| Mechanical planning | ✅ Complete |
| BOM preparation | ✅ Complete |
| Gerber generation | ✅ Complete |
| Drill-file generation | ✅ Complete |
| Manufacturing documentation | ✅ Complete |
| PCB fabrication | ⬜ Pending |
| Hardware assembly | ⬜ Pending |
| Protection firmware validation | ⬜ Pending |
| Initial power-up | ⬜ Pending |
| Calibration | ⬜ Pending |
| Audio measurements | ⬜ Pending |
| Final performance characterization | ⬜ Pending |

---

## Reference Design and Credits

The core amplifier topology is inspired by:

**Rod Elliott — Elliott Sound Products (ESP), Project 3A Power Amplifier**

Credit for the original amplifier topology belongs to **Rod Elliott / Elliott Sound Products**.

This repository documents a broader implementation built around that amplifier concept, including the project-specific:

- PCB implementation;
- component selection;
- power-supply integration;
- STM32 protection controller;
- DC monitoring;
- temperature monitoring;
- relay control;
- status indication;
- thermal strategy;
- mechanical integration;
- manufacturing preparation.

---

## Engineering Goals

The project was developed around the following priorities:

- reliable discrete Class‑AB amplification;
- loudspeaker protection;
- effective thermal management;
- low-noise PCB layout;
- intentional grounding;
- practical current handling;
- serviceable construction;
- readily sourceable components;
- clear documentation;
- reproducible fabrication files;
- a structured path from design to measured hardware validation.

---

## Author

**Stamatis Mavitzis**  
Electrical & Computer Engineering

Designed in **KiCad**.

---

<div align="center">

### Hi‑Fi Power Amplifier · Hardware Design Project

*From schematic capture to PCB manufacturing, protection, thermal management, and final hardware validation.*

</div>
