# CreatorPad Hardware Files

This directory contains the hardware design files for the CreatorPad project.

## Files

- **creatorpad.kicad_sch** - KiCad schematic showing the circuit design
- **creatorpad.kicad_pcb** - KiCad PCB layout file

## Hardware Components

### Main Microcontroller
- **ESP32-S3** - 32-bit dual-core processor with WiFi/BLE
  - USB-C for power and programming
  - GPIO pins for buttons and encoders
  - SPI/I2C support

### Input Devices
- **6x Push Buttons** - Tactile switches for shortcuts
  - Play/Pause
  - Cut
  - Undo
  - Save
  - Custom 1
  - Custom 2

- **Rotary Encoder** - EC11 or similar
  - Rotation detection (GPIO A/B)
  - Push button (GPIO SW)

### Display
- **OLED Display** - 0.96" 128x64 pixels
  - I2C interface (SDA/SCL)
  - Status and mode indication

### Power
- USB-C connector providing 5V input
- Linear regulator for 3.3V supply

## Design Notes

This is a beginner-friendly hardware project. The design uses standard components and simple I/O connections for easy prototyping and learning.

## Next Steps

1. Finalize component footprints in KiCad
2. Route PCB traces
3. Generate manufacturing files (Gerbers, drill data)
4. Order PCB prototype
5. Assemble and test

