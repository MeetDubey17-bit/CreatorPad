# CreatorPad Firmware

This directory contains firmware implementations for the CreatorPad hardware control pad.

## Available Implementations

### Arduino Sketch (creatorpad.ino)
**Language:** C/C++ (Arduino IDE compatible)
**Target:** ESP32-S3 with Arduino core

Features:
- Button debouncing and debouncing
- Rotary encoder input handling
- OLED display (I2C) updates
- Serial debug output
- Modular design for easy USB HID integration

**Requirements:**
- Arduino IDE with ESP32 board support
- Libraries:
  - Adafruit_SSD1306
  - Adafruit_GFX
  - Wire (built-in)

### MicroPython Implementation (creatorpad.py)
**Language:** Python (MicroPython)
**Target:** ESP32-S3 with MicroPython firmware

Features:
- Button state machine
- Rotary encoder pulse detection
- OLED display support via ssd1306 driver
- Clean, readable Python code
- Timer-based interrupt handling

**Requirements:**
- MicroPython firmware installed on ESP32-S3
- Libraries:
  - ssd1306
  - machine (built-in)

## Getting Started

### Arduino Setup
1. Install Arduino IDE
2. Add ESP32 board support via Board Manager
3. Install required Adafruit libraries
4. Open `creatorpad.ino` in Arduino IDE
5. Select ESP32-S3 board and USB port
6. Upload sketch

### MicroPython Setup
1. Install MicroPython on ESP32-S3 (use esptool.py)
2. Upload `creatorpad.py` to device using ampy or WebREPL
3. Create `boot.py` to auto-run the firmware on startup

## Pin Mapping

| Function | GPIO Pin |
|----------|----------|
| Button Play/Pause | 5 |
| Button Cut | 6 |
| Button Undo | 7 |
| Button Save | 8 |
| Button Custom 1 | 9 |
| Button Custom 2 | 10 |
| Encoder A | 11 |
| Encoder B | 12 |
| Encoder Switch | 13 |
| I2C SDA (OLED) | 8 |
| I2C SCL (OLED) | 9 |
| USB D+ | 18 |
| USB D- | 19 |

## Features

### Current Implementation
- ✅ Button input detection with debouncing
- ✅ Rotary encoder reading
- ✅ OLED display control
- ✅ Mode switching
- ✅ Serial debug output

### TODO / Future Features
- ⏳ USB HID keyboard/media key support
- ⏳ Custom keybinding configuration
- ⏳ Mode profiles (Adobe Premiere, DaVinci, etc.)
- ⏳ EEPROM settings storage
- ⏳ Bluetooth connectivity
- ⏳ Battery support with charging

## USB HID Integration

To send keyboard or media commands to the host computer, you'll need to:

**Arduino:**
- Use `Keyboard.h` library (if available for ESP32-S3)
- Or implement TinyUSB HID descriptors

**MicroPython:**
- Use `usb_hid` module if MicroPython build includes it
- Or use pyusb for host-side communication

## Development

### Testing
1. Open Serial Monitor (Arduino IDE) or WebREPL (MicroPython)
2. Press buttons and observe debug output
3. Rotate encoder and check mode changes
4. Verify OLED display updates

### Debugging
- Enable Serial output to monitor button presses
- Check GPIO pin levels with a multimeter
- Use oscilloscope to verify encoder signals if needed

## License

Same as main CreatorPad project license
