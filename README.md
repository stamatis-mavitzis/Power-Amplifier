# Hi-Fi Class-AB Power Amplifier

A complete discrete **Class-AB Hi-Fi power amplifier** designed in **KiCad**, including the amplifier stage, power supply, PCB layout, thermal management, and an **STM32-based speaker protection controller**.

The project was developed as a complete hardware design, from schematic capture and component selection through PCB layout, protection circuitry, BOM preparation, and manufacturing files.

The amplifier design is based on the principles of **Rod Elliott's Project 3A**, with additional changes to component selection, PCB implementation, power supply design, thermal management, and microcontroller-based protection.

---

## Project Overview

The goal of this project was to design a robust two-channel audio power amplifier using discrete components while incorporating modern protection and monitoring features.

The system consists of:

- Discrete Class-AB power amplifier channels
- ±32 V DC amplifier power supply
- 300 VA toroidal power transformer
- Large reservoir/filter capacitors
- Dedicated speaker protection system
- STM32 microcontroller
- Independent DC-output monitoring for each channel
- Dual heatsink temperature monitoring
- Delayed speaker connection at startup
- Automatic speaker disconnection during fault conditions
- Overtemperature protection
- Relay-controlled speaker outputs
- Front-panel status LEDs
- Large external heatsinks
- Forced-air cooling
- PCB ground plane and carefully considered grounding
- Through-hole power devices for easier assembly and servicing

---

## System Architecture

The amplifier is divided into several functional sections:

```text
                  ┌─────────────────────┐
                  │     Audio Input     │
                  │        RCA          │
                  └──────────┬──────────┘
                             │
                             ▼
                  ┌─────────────────────┐
                  │   Power Amplifier   │
                  │     Class-AB        │
                  │                     │
                  │  Voltage Gain Stage │
                  │  Driver Stage       │
                  │  Output Stage       │
                  └──────────┬──────────┘
                             │
                             ▼
                   ┌───────────────────┐
                   │ Protection Relay  │
                   └─────────┬─────────┘
                             │
                             ▼
                   ┌───────────────────┐
                   │ Speaker Output    │
                   └───────────────────┘


       ┌──────────────── STM32 Protection Controller ────────────────┐
       │                                                             │
       │  DC Detection L ──────► ADC                                 │
       │  DC Detection R ──────► ADC                                 │
       │  Temperature L ───────► ADC                                 │
       │  Temperature R ───────► ADC                                 │
       │                                                             │
       │               Fault / Delay Logic                           │
       │                        │                                    │
       │                Relay Drivers                                │
       │                        │                                    │
       │              Speaker Relays L/R                             │
       └─────────────────────────────────────────────────────────────┘
```

---

## Power Amplifier

The audio power stage uses a conventional discrete **Class-AB topology**.

The design contains the input, voltage amplification, biasing, driver, and complementary power output stages required for a high-current audio amplifier.

### Output Transistors

The final complementary output transistor pair is:

| Device | Type | Package |
|---|---|---|
| **2SC5200-O** | NPN power transistor | TO-3P(L), THT |
| **2SA1943-O** | PNP power transistor | TO-3P(L), THT |

These devices are mounted so that the power transistors can be attached directly to the external heatsinks.

The PCB placement was designed with the output devices positioned near the board edges to simplify the mechanical connection between the transistors and heatsinks.

---

## Power Supply

The main amplifier operates from a symmetrical power supply of approximately:

```text
+32 V
 GND
-32 V
```

The supply is generated using a:

**25-0-25 VAC / 300 VA toroidal transformer**

followed by:

```text
Transformer
    │
    ▼
Bridge Rectifier
    │
    ▼
Reservoir Capacitors
    │
    ├────────► +32 V
    │
    ├────────► GND
    │
    └────────► -32 V
```

A high-current **35 A bridge rectifier** is used for the main amplifier supply.

The high-current charging paths between the rectifier, reservoir capacitors, amplifier power rails, and ground were considered separately from the low-level audio signal paths during PCB design.

---

# STM32 Speaker Protection Controller

A dedicated microcontroller-based protection system was designed around the:

**ST NUCLEO-G031K8**

using the **STM32G031K8** microcontroller.

The controller supervises the amplifier and controls the speaker relays.

---

## Protection Functions

The protection controller implements several independent safety functions.

### Startup Delay

When the amplifier is powered on, the speakers remain disconnected during the initial startup period.

```text
POWER ON
   │
   ▼
Protection Controller Starts
   │
   ▼
Check DC Outputs
   │
   ▼
Check Temperatures
   │
   ▼
Startup Delay
   │
   ▼
Speaker Relays ON
```

This prevents startup transients from being sent directly to the loudspeakers.

---

### DC Speaker Protection

Each amplifier output is monitored independently.

The amplifier output signal passes through a dedicated conditioning circuit before reaching an STM32 ADC input.

Under normal operation, the amplifier output contains an AC audio waveform centred around approximately 0 V.

The firmware analyses the measured signal to determine whether a persistent positive or negative DC component is present.

If excessive DC is detected:

```text
DC FAULT
   │
   ▼
STM32 detects abnormal output
   │
   ▼
Speaker relay disabled
   │
   ▼
Speaker disconnected from amplifier
```

This helps protect the loudspeaker from potentially destructive amplifier failures.

---

### Temperature Monitoring

Each amplifier heatsink is monitored using a **10 kΩ NTC thermistor**.

Two independent temperature channels are provided:

```text
LEFT HEATSINK  ──► NTC ──► STM32 ADC
RIGHT HEATSINK ──► NTC ──► STM32 ADC
```

The microcontroller continuously evaluates the heatsink temperature.

If the temperature exceeds the configured safety threshold, the protection system disconnects the loudspeakers.

The system also provides monitoring for abnormal temperature-sensor conditions.

---

## Speaker Relays

Speaker outputs are controlled using two:

**Omron G2RL-1A-E-DC12**

12 V relays.

One relay is used for each amplifier channel.

The STM32 does not drive the relay coils directly. Each relay uses a transistor driver stage.

The relay driver uses:

- BC337 NPN transistor
- Base resistor
- Flyback diode
- 12 V relay supply

The flyback diode protects the transistor and surrounding electronics from the inductive voltage generated when the relay coil is switched off.

---

## Status Indicators

Front-panel LEDs provide information about the current protection state.

Indicators are provided for conditions such as:

- Amplifier startup / speaker delay
- Normal operation
- DC fault
- Temperature sensor fault
- Overtemperature condition
- Speaker protection activation

This allows the operating state of the protection system to be identified without external diagnostic equipment.

---

# Thermal Management

The power output transistors are designed to be mounted to large external heatsinks.

The thermal design includes:

- Dedicated heatsink for each amplifier channel
- NTC temperature sensor on each heatsink
- Thermal protection through the STM32 controller
- Forced-air cooling
- Four AC cooling fans
- Mechanical orientation of the power transistors toward the PCB edges

Adequate electrical isolation must be used between the transistor mounting tabs and heatsinks where required.

---

# PCB Design

The complete amplifier electronics were designed using **KiCad**.

PCB design considerations included:

- High-current power traces
- Short output-stage current paths
- Separation of sensitive audio signals from power wiring
- Ground-plane implementation
- Signal-ground management
- Power-ground management
- Thermal placement of power devices
- Through-hole power components
- Accessible test points
- Relay-current routing
- Connector placement
- Mounting holes
- Silkscreen component identification
- Mechanical clearance around heatsinks

---

## Grounding

Grounding is particularly important in high-power audio equipment.

The design separates the conceptual roles of:

```text
SIGNAL GROUND
      │
      │
      ▼
CENTRAL GROUND / STAR POINT
      ▲
      │
      │
POWER GROUND
```

Sensitive input and feedback currents are prevented from sharing long PCB paths with large rectifier, reservoir-capacitor, or speaker-return currents.

The speaker return belongs to the high-current section of the grounding system rather than the sensitive input-signal ground.

This layout strategy helps reduce hum, ground-loop problems, and unwanted coupling between the power supply and audio signal.

---

# Main Components

Some of the major components used in the amplifier are listed below.

| Component | Device |
|---|---|
| NPN output transistor | 2SC5200-O |
| PNP output transistor | 2SA1943-O |
| Protection MCU board | ST NUCLEO-G031K8 |
| Microcontroller | STM32G031K8 |
| Speaker relays | Omron G2RL-1A-E-DC12 |
| Relay driver transistor | BC337 |
| Temperature sensors | 10 kΩ NTC |
| Main transformer | 25-0-25 VAC, 300 VA toroidal |
| Main bridge rectifier | 35 A bridge rectifier |
| Main supply | Approximately ±32 V DC |
| Speaker connectors | Gold-plated binding terminals |
| Audio inputs | RCA connectors |

A complete manufacturing BOM is provided separately in the repository.

---

# Repository Structure

The repository is organised so that design files, documentation, manufacturing files, and custom libraries remain separate.

```text
Power-Amplifier/
│
├── README.md
│
├── Documentation/
│   ├── Schematics/
│   ├── PDF/
│   └── Images/
│
├── KiCad/
│   ├── Schematics/
│   └── PCB/
│
├── Libraries/
│   ├── Symbols/
│   ├── Footprints/
│   └── 3D_Models/
│
├── Manufacturing/
│   ├── Gerber/
│   └── Drill/
│
└── BOM/
    └── Power_Amplifier_BOM.csv
```

---

# Schematics

The project documentation includes schematics for the major functional sections.

### Power Amplifier

Contains the complete discrete audio amplifier circuitry.

### Main Power Supply

Contains the transformer, rectifier, filtering, and symmetrical supply rails used by the amplifier.

### Protection Controller

Contains:

- STM32 development board connections
- DC sensing circuits
- Temperature sensing
- Speaker relay drivers
- Status LEDs
- Protection-controller power supply

---

# Manufacturing Files

PCB manufacturing outputs include:

- Gerber files
- Copper layers
- Solder mask
- Silkscreen
- Edge.Cuts
- Plated-through-hole drill file
- Non-plated-through-hole drill file

These files are stored separately from the original KiCad design files to keep the repository organised.

---

# Bill of Materials

Component selection was performed with attention to:

- Electrical ratings
- Power dissipation
- Package compatibility
- KiCad footprint compatibility
- Through-hole mounting where appropriate
- Manufacturer availability
- Distributor stock
- Mechanical dimensions
- Thermal requirements

Manufacturer part numbers and distributor order codes are included in the BOM.

---

# Mechanical Design

The amplifier was designed with practical assembly and enclosure integration in mind.

Mechanical considerations include:

- PCB mounting holes
- Large external heatsinks
- Front-panel LEDs
- RCA input connectors
- Gold-plated speaker terminals
- Mains power switch
- Fuse holders
- Cooling fans
- Toroidal transformer mounting
- Cable management
- Spade connections for high-current wiring

Power devices are positioned to simplify attachment to the heatsinks while keeping high-current PCB paths short.

---

# Safety

This amplifier contains potentially hazardous voltages and high stored energy.

Large filter capacitors can retain charge after the equipment has been disconnected from mains power.

The design therefore requires appropriate:

- Mains fuse protection
- Protective earth connection
- Insulation
- Wire ratings
- Connector ratings
- Transformer mounting
- PCB creepage and clearance
- Chassis grounding
- Strain relief
- Heatsink insulation

The amplifier should never be serviced while connected to mains power.

---

# Design Tools

The project was developed primarily with:

- **KiCad** — schematic capture and PCB design
- **Mouser Electronics** — component sourcing
- Manufacturer datasheets — electrical and mechanical verification
- Git / GitHub — revision control and project documentation

---

# Project Goals

The project combines a traditional discrete audio power amplifier with a modern protection platform.

The main engineering goals were:

- Reliable discrete Class-AB amplification
- Robust speaker protection
- Effective thermal management
- Low-noise PCB layout
- Proper grounding
- Serviceable through-hole construction
- Readily available components
- Professional PCB documentation
- Reproducible manufacturing files
- Clear repository organisation

---

# Reference Design

The amplifier topology was inspired by:

**Rod Elliott — ESP Project 3A Power Amplifier**

The PCB implementation, component selection, protection controller, power supply implementation, thermal monitoring, mechanical integration, and supporting electronics were developed specifically for this project.

Credit for the original amplifier topology belongs to **Rod Elliott / Elliott Sound Products**.

---

# Author

**Stamatis Mavitzis**

Electrical & Computer Engineering

Designed using KiCad.

---

# Project Status

The electrical and PCB design phase of the project is complete.

Current project status:

- Power amplifier schematic completed
- Main power supply schematic completed
- STM32 protection controller designed
- DC sensing circuitry designed
- Temperature monitoring circuitry designed
- Speaker relay control designed
- Status indicator circuitry designed
- Component selection completed
- Footprints assigned
- PCB layout completed
- Grounding strategy implemented
- Mechanical mounting considerations completed
- Bill of Materials prepared
- Gerber files generated
- Drill files generated
- Manufacturing documentation prepared

The next stage of the project is physical PCB fabrication, assembly, firmware development, initial power-up, testing, calibration, and performance measurements.

Measured amplifier performance will be documented after hardware validation and testing.