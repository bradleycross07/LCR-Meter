# Aestrum Electronics – LCR Meter

A low-cost LCR (component) meter for secondary-school electronics, designed by
**Aestrum Electronics** (Group B5) for the University of York module
**ELE00061I Electronics Project 2** (2026/27), in response to the
*Electronics in Schools* Call to Tender (ref. UKG/DE/ESI/TG/2026/06).

The meter measures resistance, capacitance and inductance and shows the
result on a 16×2 LCD.

## How it works (overview)

A sine wave from an AD9833 signal generator drives the component under test
through a known reference resistor. The STM32's ADC samples the voltages
(buffered by an MCP6004 op-amp), and the firmware calculates the component's
impedance and converts it to R, C or L. The test frequency (100 Hz, 1 kHz or
10 kHz) is chosen to keep the impedance in a measurable range.

| Subsystem          | Part / approach                                              |
| ------------------ | ------------------------------------------------------------ |
| Microcontroller    | NUCLEO-G071RB (STM32G071RB) for the prototype                |
| Signal generation  | AD9833 DDS, 100 Hz / 1 kHz / 10 kHz                          |
| Analogue front end | MCP6004 quad op-amp buffers                                  |
| Display / controls | 16×2 LCD, *Mode* (R/C/L) and *Hold* buttons, terminal block |
| Power              | USB via the Nucleo (prototype); 2×AA (production)            |
| Firmware           | C, STM32CubeIDE / STM32CubeMX, HAL                           |

### Target performance (provisional – to be confirmed by testing)

| Component   | Range            | Accuracy |
| ----------- | ---------------- | -------- |
| Resistance  | 10 Ω – 1 MΩ      | ±5 %     |
| Capacitance | 1 nF – 100 µF    | ±5 %     |
| Inductance  | 1 mH – 1 H       | ±10 %    |

## Repository layout

| Folder                   | Contents                                      |
| ------------------------ | --------------------------------------------- |
| [`firmware/`](firmware/) | STM32CubeIDE project for the meter's firmware |

Meeting minutes, weekly progress reports, the test plan and the group reports
live in the shared Google Drive, not in this repository.

## Team

| Member    | Roles                                                  |
| --------- | ------------------------------------------------------ |
| Mackenzie | Documentation Leader, Test Leader                      |
| Juncheng  | Hardware Leader, PCB Design Leader                     |
| Raisa     | User Interface Programming Leader, Mechanical Design Leader |
| Tabiso    | Application Leader, Team Leader                        |
| Bradley   | Software Version Controller, Embedded Programming Leader |
| Douman    | Marketing Leader, Production / Sustainability Leader   |

## Contributing

All changes go through a pull request into `main` and must be reviewed before
merging. See [CONTRIBUTING.md](CONTRIBUTING.md) for branch naming, commit
messages and the review process.
