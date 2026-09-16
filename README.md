<div align="center">

# Hi‑Fi Class‑AB Power Amplifier

### Discrete stereo power amplifier with STM32 speaker protection, thermal monitoring, firmware, BOM, and production-ready KiCad files

**KiCad · Discrete Class‑AB · ±32 V Rails · STM32G031K8 · Speaker Protection · Thermal Monitoring**

![KiCad](https://img.shields.io/badge/EDA-KiCad-314CB0?style=flat-square)
![Topology](https://img.shields.io/badge/Topology-Class--AB-444444?style=flat-square)
![MCU](https://img.shields.io/badge/MCU-STM32G031K8-03234B?style=flat-square)
![Supply](https://img.shields.io/badge/Main%20Rails-%C2%B132%20V-555555?style=flat-square)

</div>

---

## Overview

This repository contains the engineering design of a two-channel discrete **Hi‑Fi Class‑AB power amplifier** developed in **KiCad**.

The power-amplifier stage is based on the design principles of **Rod Elliott's ESP Project 3A**, while this implementation expands the reference design into a complete stereo system with custom PCB layouts, a dual-transformer power architecture, updated production components, thermal management, and a dedicated **STM32-based speaker protection controller**.

The repository covers the complete design-to-fabrication workflow:

- stereo power-amplifier, power-supply, and protection schematics;
- STM32 protection firmware and source structure;
- finalized PCB layouts and grounding strategy;
- verified component/footprint assignments;
- final sourcing-oriented BOM revisions;
- thermal and mechanical integration planning;
- Gerber and PTH/NPTH drill generation;
- fabrication, assembly, testing, and safety documentation.

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
- [Final Hardware Revisions](#final-hardware-revisions)
- [Repository Structure](#repository-structure)
- [Schematics and Documentation](#schematics-and-documentation)
- [Manufacturing Files](#manufacturing-files)
- [Bill of Materials](#bill-of-materials)
- [Mechanical Integration](#mechanical-integration)
- [Bring-Up and Validation](#bring-up-and-validation)
- [Safety](#safety)
- [Design Tools](#design-tools)
- [Reference Design and Credits](#reference-design-and-credits)
- [Author](#author)

---

## Key Features

### Audio Power Stage

- Two-channel discrete **Class‑AB** architecture
- Complementary bipolar output stage
- **2SC5200-O / 2SA1943-O** complementary output transistor pair
- Through-hole power devices for serviceability and heatsink mounting
- Short high-current output paths
- Dedicated external heatsinking for each amplifier channel

### Main Power Supply

- Approximately **±32 V DC** amplifier supply rails
- **2 × 300 VA** toroidal transformers for the stereo power stage
- High-current bridge rectification and reservoir filtering
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
- Chassis-mounted heatsinking using passive natural-convection cooling
- PCB mounting holes and enclosure integration
- High-current spade and terminal connections where appropriate

---

## Technical Summary

| Parameter | Design |
|---|---|
| Amplifier topology | Discrete Class‑AB |
| Number of channels | 2 |
| Main DC rails | Approximately ±32 V |
| Main transformers | **2 × 300 VA toroidal**, approximately 2 × 24/25 VAC secondaries |
| Output devices | **2SC5200-O (NPN) / 2SA1943-O (PNP)** |
| Output-device package | **TO‑3P, through-hole** |
| Protection controller | ST NUCLEO‑G031K8 |
| MCU | STM32G031K8 |
| Speaker relays | 2 × Omron G2RL‑1A‑E‑DC12 |
| Relay driver | BC337 NPN |
| Temperature sensing | 2 × 10 kΩ NTC |
| Cooling | External chassis heatsinks, passive natural-convection cooling |
| Audio inputs | RCA |
| Speaker outputs | Gold-plated binding terminals |
| PCB CAD | KiCad |

### Validation Scope

The README deliberately separates the documented design from **measured audio characterization**. Values such as output power, THD, frequency response, signal-to-noise ratio, and thermal rise should only be published together with the exact load, signal level, test equipment, and measurement conditions.

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

                 230 VAC MAINS
                      │
          ┌───────────┴───────────┐
          ▼                       ▼
  300 VA TOROIDAL #1      300 VA TOROIDAL #2
   ~2 × 24/25 VAC          ~2 × 24/25 VAC
          │                       │
          ▼                       ▼
  RECTIFIER + FILTER      RECTIFIER + FILTER
          │                       │
          ▼                       ▼
   LEFT ±32 V RAILS        RIGHT ±32 V RAILS
          │                       │
          ▼                       ▼
   LEFT AMPLIFIER          RIGHT AMPLIFIER
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

The final complementary output pair used in the amplifier is:

| Reference | Device | Polarity | Package |
|---|---|---|---|
| **Q7** | **2SA1943-O** | PNP | TO-3P |
| **Q8** | **2SC5200-O** | NPN | TO-3P |

The devices are mounted using vertical **TO-3P through-hole** footprints and are positioned near the PCB edge for direct mounting to the external chassis heatsinks. Appropriate thermal interface material and electrical insulation must be used where required.


---

## Power Supply

The final stereo implementation uses a **dual-transformer power architecture** sized around **two 300 VA toroidal transformers**. Each transformer provides approximately **2 × 24/25 VAC**, producing roughly **±32 V DC** rails after bridge rectification and reservoir filtering under normal operating conditions.

```text
230 VAC MAINS
     │
     ├────────► 300 VA TOROID #1 ─► RECTIFIER/FILTER ─► LEFT ±32 V
     │
     └────────► 300 VA TOROID #2 ─► RECTIFIER/FILTER ─► RIGHT ±32 V
```

This arrangement supports the stereo amplifier with substantial power-supply headroom and reduces shared supply impedance between channels.

The high-current supply uses heavy-current bridge rectification and large reservoir capacitors. Rectifier and capacitor charging loops are treated as noisy, high-current paths and are kept separate from sensitive input, feedback, and small-signal ground returns.

### Power-Supply Design Priorities

- short transformer-to-rectifier wiring;
- short rectifier-to-reservoir-capacitor paths;
- deliberate central/star grounding;
- high-current speaker return paths kept away from input ground;
- chassis protective earth bonded independently and securely;
- appropriately rated mains fusing, switchgear, cable, and insulation.

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

## STM32 Firmware

The protection firmware was implemented for the **STM32G031K8** and is maintained in:

```text
Firmware/
└── STM32/
```

The firmware is responsible for the real-time supervision of both amplifier channels and for controlling the speaker relays and status indicators.

### Firmware Responsibilities

The implemented firmware performs:

- system initialization;
- ADC acquisition for left and right DC sensing;
- ADC acquisition for left and right NTC temperature sensing;
- startup-delay timing;
- relay-control logic;
- DC-fault qualification;
- overtemperature detection;
- sensor-fault handling;
- front-panel LED control;
- safe-state handling during detected faults.

### Protection State Flow

```text
POWER ON
   │
   ▼
MCU INITIALIZATION
   │
   ▼
ADC AND GPIO INITIALIZATION
   │
   ▼
STARTUP DELAY
   │
   ▼
CHECK DC AND TEMPERATURE INPUTS
   │
   ├──── Fault detected ───► RELAYS OFF
   │
   └──── Safe condition ───► RELAYS ON
                                 │
                                 ▼
                       CONTINUOUS MONITORING
                                 │
                ┌────────────────┴────────────────┐
                │                                 │
          Normal condition                  Fault condition
                │                                 │
                ▼                                 ▼
          RELAYS REMAIN ON                  RELAYS DISABLED
```

The default safety philosophy is fail-safe: the loudspeakers are connected only when the controller has completed initialization and all monitored conditions are within the permitted operating state.

### Firmware Structure

The firmware is organized so that sensing, protection logic, and output control remain logically separated.

```text
STM32 firmware
│
├── Hardware initialization
│   ├── GPIO
│   ├── ADC
│   └── timing resources
│
├── Measurement layer
│   ├── left DC channel
│   ├── right DC channel
│   ├── left NTC channel
│   └── right NTC channel
│
├── Protection logic
│   ├── startup delay
│   ├── DC fault handling
│   ├── temperature fault handling
│   └── sensor fault handling
│
└── Output control
    ├── left speaker relay
    ├── right speaker relay
    └── status LEDs
```

This separation makes the firmware easier to test, maintain, and extend.

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
- **passive natural-convection cooling only**;
- **no cooling fans are used**;
- power-transistor placement close to PCB edges;
- mechanical clearance for transistor mounting hardware.

Thermal compound, insulators, bushings, and mounting torque should be selected according to the actual output-device and heatsink installation.

The thermal design includes the intended heatsink and airflow provisions; numerical temperature-rise claims should be added only from controlled load testing with the final chassis and airflow arrangement.

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
| NPN output transistor | **2SC5200-O** |
| PNP output transistor | **2SA1943-O** |
| Protection development board | **ST NUCLEO‑G031K8** |
| Microcontroller | **STM32G031K8** |
| Speaker relays | **Omron G2RL‑1A‑E‑DC12** |
| Relay driver transistor | **BC337** |
| Temperature sensors | **10 kΩ NTC thermistors** |
| Main transformers | **2 × 300 VA toroidal**, approx. 2 × 24/25 VAC secondaries |
| Main rectification | High-current bridge rectifiers |
| Amplifier supply | Approximately **±32 V DC per channel** |
| Standard resistors | **0.5 W, 1%** where no higher power rating is specified |
| Output emitter resistors | **R13 / R14: 0.33 Ω, 5 W wirewound** |
| R15 | **10 Ω, 0.5 W** |
| Audio input | RCA connectors |
| Speaker output | Gold-plated binding terminals |
| Cooling | External chassis heatsinks, passive natural-convection cooling |

The complete sourcing list, quantities, manufacturer part numbers, and Mouser order codes are maintained in the project BOM.

---

## Final Hardware Revisions

The release README reflects the final component changes made during the BOM and PCB review:

- The final output-transistor pair is **Q7: 2SA1943-O (PNP)** and **Q8: 2SC5200-O (NPN)**.
- Both output devices use **TO-3P through-hole** packages.
- Output-device package is **TO‑3P** with B-C-E lead order.
- General resistors without an explicit power requirement were standardized to **0.5 W** parts.
- **R15 (10 Ω)** was standardized to **0.5 W**.
- **R13 and R14 (0.33 Ω)** were finalized as **5 W wirewound** resistors.
- The chassis/power architecture is sized for **two 300 VA toroidal transformers** rather than a single transformer.
- The BOM and manufacturing documentation are treated as release outputs rather than work-in-progress files.


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

The BOM is a finalized sourcing document rather than a preliminary component list. It is maintained separately from the schematic source so it can be imported into distributor tools and revised without cluttering the electrical drawings.

### Final BOM Rules

- standard resistors with no explicit higher-power requirement: **0.5 W**;
- standard tolerance target: **1%** where applicable;
- **R13 and R14: 0.33 Ω, 5 W wirewound**;
- **R15: 10 Ω, 0.5 W**;
- **Q7: 2SA1943-O PNP**;
- **Q8: 2SC5200-O NPN**;
- part selection checked against package/footprint compatibility;
- distributor/manufacturer part numbers retained for order preparation;
- quantities can be maintained in assembly or doubled-order versions as required.

Component selection considers electrical ratings, dissipation, tolerance, package, KiCad footprint, distributor availability, mechanical dimensions, thermal requirements, and serviceability.

---

## Mechanical Integration

The project is designed as a complete amplifier assembly rather than only an isolated PCB.

Mechanical considerations include:

- PCB mounting holes;
- amplifier heatsinks;
- output-transistor mounting;
- NTC placement;
- passive airflow around the external heatsinks;
- no cooling fans or fan-mounting provisions;
- mounting and spacing for **two 300 VA toroidal transformers**;
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

## Bring-Up and Validation

A complete bring-up and validation sequence is included as part of the engineering release so that the manufactured hardware can be commissioned in a controlled and repeatable way.

### Validation Procedure

1. **Visual and assembly inspection**
   - verify component orientation and polarity;
   - verify 2SA1943-O / 2SC5200-O pinout, footprint, and mounting insulation;
   - verify diode, relay, connector, and electrolytic orientation;
   - inspect mains clearances and protective-earth bonding.

2. **Unpowered electrical checks**
   - check continuity and unintended shorts;
   - verify rail-to-ground resistance behaviour;
   - verify ground connectivity and speaker-return routing;
   - inspect output-stage connections before applying power.

3. **Power-supply validation**
   - verify both transformer secondary connections;
   - verify bridge-rectifier polarity;
   - measure left and right positive/negative rails;
   - confirm protection-controller supply voltage.

4. **Controlled first power-up**
   - use a current-limited or otherwise controlled first-power method;
   - monitor idle current, output DC offset, and transistor temperature;
   - keep loudspeakers disconnected until the amplifier is proven stable.

5. **Protection-system validation**
   - verify startup delay;
   - verify left/right relay drive;
   - verify DC-fault detection;
   - verify NTC sensing and thermal shutdown behaviour;
   - verify LED/status indications.

6. **Signal-path validation**
   - apply a known low-level test signal;
   - verify both channels with an oscilloscope and suitable dummy load;
   - increase signal level progressively while monitoring current and temperature.

7. **Quantitative characterization**
   - output power;
   - frequency response;
   - THD / distortion;
   - DC offset;
   - thermal rise under sustained load;
   - protection thresholds and response behaviour.

### Validation Philosophy

The project documentation distinguishes between **functional validation** and **quantitative audio characterization**.

Functional and quantitative test results should be recorded against the documented procedure so that later published performance figures remain traceable to real measurements.

Precise audio-performance figures should be reported only with documented test equipment, load impedance, signal conditions, and measurement methodology.

---

## Safety

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

The project implements the following engineering objectives:

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
- a complete path from design and firmware through fabrication, assembly, and measured hardware validation.

---

## Author

**Stamatis Mavitzis**  
Electrical & Computer Engineering

Designed in **KiCad**.

---

<div align="center">

### Hi‑Fi Power Amplifier · Engineering Project

*Design documentation covering amplifier electronics, dual-transformer power, PCB manufacturing, STM32 protection firmware, BOM control, thermal management, and validation procedures.*

</div>
