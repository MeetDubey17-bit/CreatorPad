# CreatorPad Fabrication Readiness Checklist

This project cannot generate genuine Gerber and Excellon output until the PCB is fully defined in KiCad. The current `hardware/creatorpad.kicad_pcb` and `hardware/creatorpad.kicad_sch` files are still placeholder files and are not manufacturing-ready.

## Required fixes before fabrication export

### 1. Complete the schematic with actual components
The schematic must include the real electrical parts for the design:
- ESP32-S3 module
- USB-C connector
- 0.96" OLED display
- rotary encoder (EC11)
- six tactile push buttons
- decoupling capacitors
- pull-up resistors
- LED and current-limiting resistor (if used)
- power routing and ground net

Each component must have:
- correct reference designator
- correct value
- correct footprint assignment
- valid pin mapping

### 2. Run Electrical Rule Check (ERC)
In KiCad:
- open the schematic editor
- run `Inspect -> Electrical Rules Checker`
- fix all warnings/errors
- make sure there are no unconnected or invalid power pins

### 3. Assign KiCad footprints
Every part must be assigned to a proper footprint.
Examples:
- ESP32-S3 module footprint
- USB-C receptacle footprint
- OLED breakout footprint
- EC11 rotary encoder footprint
- tactile switch footprint
- passives on 0603/0805/through-hole packages according to your layout

### 4. Create a real PCB layout
The PCB file must contain:
- actual component placement
- board outline (`Edge.Cuts`)
- copper zones / traces for power and signals
- ground plane or copper pour
- proper component rotation and spacing
- layout suitable for hand assembly or manufacturing

### 5. Route all nets
Make sure the following are connected as designed:
- ESP32-S3 power and ground
- USB-C D+ / D- data lines
- I2C bus to OLED (SDA/SCL)
- 6 button input lines
- encoder A/B/SW lines
- reset and enable lines as needed
- all pull-ups / pull-downs

### 6. Confirm board dimensions and mechanical fit
Check:
- overall board size matches intended enclosure
- button spacing is correct
- OLED display placement is correct
- encoder knob clearance is sufficient
- USB-C port accessibility is correct
- mounting holes or standoffs are positioned appropriately

### 7. Run DRC checks
In KiCad PCB editor:
- run `Tools -> Design Rules Check`
- resolve all violations
- confirm track width, clearance, annular ring, and via rules are valid

### 8. Generate final fabrication output only after DRC passes
Once the board is fully complete and DRC clean:
- export Gerbers
- export drill files (Excellon)
- validate the output with KiCad plot preview or a Gerber viewer
- zip the result into `fabrication/CreatorPad_Gerbers.zip`

### 9. Validate generated files before release
Before packaging for manufacturing, check:
- all copper layers are present
- board outline is correct
- drill file matches pads and holes
- silkscreen is readable
- solder mask and paste layers are included when needed
- no ghost layers or accidental duplicates exist

## Current status of this repo
The board is not ready for production export yet. The files currently present are concept placeholders only and do not contain a complete routed PCB.

## What to do next
1. Finish the schematic in `hardware/creatorpad.kicad_sch`
2. Add actual footprints and component placement in `hardware/creatorpad.kicad_pcb`
3. Route the full board
4. Run ERC + DRC until zero errors
5. Export Gerbers and drill files
6. Zip the output into `fabrication/CreatorPad_Gerbers.zip`

This is the exact minimum set of work required before a genuine fabrication package can be created.
