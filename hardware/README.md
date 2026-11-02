# hardware

Schematics, circuit simulations and PCB design files for the LCR meter.

## What goes here

| Folder         | Contents                                                |
| -------------- | ------------------------------------------------------- |
| `schematics/`  | Schematic source files, plus a PDF export of each       |
| `simulation/`  | Circuit simulation files and results                    |
| `pcb/`         | PCB layout source files                                 |
| `fabrication/` | Gerbers / drill files exactly as submitted for printing |
| `bom/`         | Bill of materials (with supplier part numbers and cost) |

Commit the native design files **and** a PDF export, so anyone can view the
design without the CAD tool installed.

## Main components

| Part          | Purpose                                 |
| ------------- | --------------------------------------- |
| NUCLEO-G071RB | Microcontroller (prototype)             |
| AD9833        | Sine-wave signal generator (SPI)        |
| MCP6004       | Quad op-amp, buffers the generator and ADC inputs |
| 16×2 LCD      | Display                                 |
