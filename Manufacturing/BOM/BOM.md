# Power Amplifier Bill of Materials

This BOM is generated from the KiCad **power amplifier** and **power supply** schematics. It represents one complete channel board, with an additional quantity column for a stereo build using two identical boards.

## Scope

- Included: `power_amplifier.kicad_sch` and `power_supply.kicad_sch`.
- Cross-checked against: `Power Amplifier Rod Elliot Project 3A.kicad_pcb`.
- Excluded: preamplifier, STM32 protection controller, chassis hardware, transformers, heatsinks, external RCA/speaker terminals, and cabling.
- Power/ground symbols and KiCad power flags are excluded from the BOM.

## BOM

| Category | Description | Value / Part | Qty / Channel | Qty Stereo | References / Board | Footprint | Notes |
|---|---|---:|---:|---:|---|---|---|
| Resistor | Through-hole resistor | 0R33 | 2 | 4 | R13, R14 | `Resistor_THT:R_Axial_Power_L25.0mm_W9.0mm_P30.48mm` |  |
| Resistor | Through-hole resistor | 10 | 1 | 2 | R15 | `Resistor_THT:R_Axial_DIN0516_L15.5mm_D5.0mm_P20.32mm_Horizontal` |  |
| Resistor | Through-hole resistor | 1K | 4 | 8 | R1, R3, R4, R16 | `Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal` |  |
| Resistor | Through-hole resistor | 220 | 1 | 2 | R12 | `Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal` |  |
| Resistor | Through-hole resistor | 22K | 3 | 6 | R2, R5, R8 | `Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal` |  |
| Resistor | Through-hole resistor | 3K3 | 3 | 6 | R9, R10, R11 | `Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal` |  |
| Resistor | Through-hole resistor | 560 | 2 | 4 | R6, R7 | `Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal` |  |
| Capacitor | Through-hole capacitor | 100n | 5 | 10 | C7, C8, C12, C13, C18 | `Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm` |  |
| Capacitor | Through-hole capacitor | 100p | 3 | 6 | C2, C4, C6 | `Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm` |  |
| Capacitor | Polarized electrolytic capacitor | 100u | 4 | 8 | C3, C5, C10, C11 | `Capacitor_THT:CP_Radial_D13.0mm_P5.00mm` | Capacitor voltage rating is not specified in the schematic. |
| Capacitor | Polarized electrolytic capacitor | 4.7u | 1 | 2 | C1 | `Capacitor_THT:CP_Radial_D10.0mm_P3.50mm` | Capacitor voltage rating is not specified in the schematic. |
| Capacitor | Polarized electrolytic capacitor | 4700u | 4 | 8 | C14, C15, C16, C17 | `Capacitor_THT:CP_Radial_D25.0mm_P10.00mm_SnapIn` | Current power-supply schematic value is 4700 µF; voltage rating is not specified in the source. |
| Trimmer | 2 kΩ vertical trimmer potentiometer | 2K | 1 | 2 | VR1 | `Potentiometer_THT:Potentiometer_Runtron_RM-065_Vertical` |  |
| Transistor | Small-signal BJT | BC546 | 4 | 8 | Q1, Q2, Q3, Q9 | `Package_TO_SOT_THT:TO-92_Inline` |  |
| Transistor | Driver / bias-stage BJT | BD139 MJE15034 | 1 | 2 | Q5 | `Package_TO_SOT_THT:TO-126-3_Vertical` | KiCad value contains alternative transistor names; the assigned footprint is TO-126. Choose one device and verify its pinout/package before assembly. |
| Transistor | Driver / bias-stage BJT | BD140 MJE15035 | 2 | 4 | Q4, Q6 | `Package_TO_SOT_THT:TO-126-3_Vertical` | KiCad value contains alternative transistor names; the assigned footprint is TO-126. Choose one device and verify its pinout/package before assembly. |
| Transistor | Power output BJT | MJL21193G | 1 | 2 | Q7 | `Package_TO_SOT_THT:TO-264-3_Vertical` |  |
| Transistor | Power output BJT | MJL21194G | 1 | 2 | Q8 | `Package_TO_SOT_THT:TO-264-3_Vertical` |  |
| LED / Diode | 5 mm through-hole LED | LED | 1 | 2 | D1 | `LED_THT:LED_D5.0mm` | LED color is not specified in the schematic. |
| Bridge Rectifier | KBPC3506WP bridge rectifier | Diotec KBPC3506WP | 1 | 2 | BR1 | `Diode_THT:Diode_Bridge_28.6x28.6x7.3mm_P18.0mm_P11.6mm` |  |
| Fuse | 3 A fuse position with PCB 5×20 mm holder footprint | 3A | 2 | 4 | F1, F2 | `Fuse:Fuseholder_Cylinder-5x20mm_Stelvio-Kontek_PTF78_Horizontal_Open` | Fit a 3 A fuse in the 5×20 mm PCB fuse holder. |
| Wire Connection | PCB solder-wire connection | +35V | 2 | 4 | J3, J10 | `Connector_Wire:SolderWire-0.127sqmm_1x01_D0.48mm_OD1mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |
| Wire Connection | PCB solder-wire connection | -35V | 2 | 4 | J4, J11 | `Connector_Wire:SolderWire-0.127sqmm_1x01_D0.48mm_OD1mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |
| Wire Connection | PCB solder-wire connection | AUDIO IN | 1 | 2 | J1 | `Connector_Wire:SolderWire-6sqmm_1x01_D3.5mm_OD7mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |
| Wire Connection | PCB solder-wire connection | COM | 1 | 2 | J7 | `Connector_Wire:SolderWire-6sqmm_1x01_D3.5mm_OD7mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |
| Wire Connection | PCB solder-wire connection | GND | 2 | 4 | J2, Jw1 | `Connector_Wire:SolderWire-6sqmm_1x01_D3.5mm_OD7mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |
| Wire Connection | PCB solder-wire connection | GND | 1 | 2 | J9 | `Connector_Wire:SolderWire-0.127sqmm_1x01_D0.48mm_OD1mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |
| Wire Connection | PCB solder-wire connection | SPEAKER OUT | 1 | 2 | J5 | `Connector_Wire:SolderWire-6sqmm_1x01_D3.5mm_OD7mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |
| Wire Connection | PCB solder-wire connection | V+ | 1 | 2 | J6 | `Connector_Wire:SolderWire-6sqmm_1x01_D3.5mm_OD7mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |
| Wire Connection | PCB solder-wire connection | V- | 1 | 2 | J8 | `Connector_Wire:SolderWire-6sqmm_1x01_D3.5mm_OD7mm` | This is a solder-wire PCB connection, not a separate plug/socket component. |

## Validation Notes

- Schematic component count per channel board: **59** populated schematic items (excluding power symbols/flags).
- Stereo schematic count: **118** items before separating fuse inserts from holders or adding off-board hardware.
- PCB reference check: the PCB contains duplicate annotated reference(s): `J7`. The BOM follows the schematic quantity, not the duplicated PCB reference.
- The PCB also contains **4** unannotated `REF**` footprint(s); these are not included because they are not defined as schematic BOM items.
- `Q4/Q6` are labelled `BD140 MJE15035` and `Q5` is labelled `BD139 MJE15034` in KiCad. Those fields contain alternatives, while the assigned footprints are TO-126; verify the exact chosen transistor and pinout before ordering/assembly.
- Capacitor voltage ratings and most resistor power ratings are not encoded in the current schematics, so they are intentionally not invented in this BOM.
- `F1` and `F2` use PCB 5×20 mm fuse-holder footprints with a schematic value of 3 A; the physical build needs both the holders and appropriate 3 A fuse inserts.
