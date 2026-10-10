"""
CreatorPad - MicroPython Firmware
ESP32-S3 MicroPython Implementation

This firmware handles button inputs, rotary encoder, and OLED display
for a video editing shortcut pad.
"""

from machine import Pin, I2C, Timer
from ssd1306 import SSD1306_I2C
import time

# OLED Display
i2c = I2C(0, scl=Pin(9), sda=Pin(8), freq=400000)
display = SSD1306_I2C(128, 64, i2c)

# GPIO Pin Definitions
BTN_PLAY = Pin(5, Pin.IN, Pin.PULL_UP)
BTN_CUT = Pin(6, Pin.IN, Pin.PULL_UP)
BTN_UNDO = Pin(7, Pin.IN, Pin.PULL_UP)
BTN_SAVE = Pin(8, Pin.IN, Pin.PULL_UP)
BTN_CUSTOM1 = Pin(9, Pin.IN, Pin.PULL_UP)
BTN_CUSTOM2 = Pin(10, Pin.IN, Pin.PULL_UP)

ENC_A = Pin(11, Pin.IN, Pin.PULL_UP)
ENC_B = Pin(12, Pin.IN, Pin.PULL_UP)
ENC_SW = Pin(13, Pin.IN, Pin.PULL_UP)

# State variables
current_mode = 1
encoder_value = 0
last_encoder_value = 0
debounce_delay = 50
last_debounce_time = 0

# Button states
button_states = {
    'PLAY': BTN_PLAY,
    'CUT': BTN_CUT,
    'UNDO': BTN_UNDO,
    'SAVE': BTN_SAVE,
    'CUSTOM1': BTN_CUSTOM1,
    'CUSTOM2': BTN_CUSTOM2,
}

def display_mode():
    """Update display with current mode"""
    display.fill(0)
    display.text('CreatorPad', 0, 0)
    display.text(f'Mode: {current_mode}', 0, 16)
    display.text('Ready', 0, 32)
    display.show()

def display_button_press(button_name):
    """Display button press feedback"""
    display.fill(0)
    display.text('Button Pressed:', 0, 0)
    display.text(button_name, 0, 16)
    display.show()
    time.sleep(0.5)
    display_mode()

def handle_button_press(button_name):
    """Handle button press event"""
    print(f"Button Pressed: {button_name}")
    display_button_press(button_name)
    
    # TODO: Send USB HID keyboard/media commands
    # Example: Play/Pause would send media key

def handle_encoder_rotation(direction):
    """Handle rotary encoder rotation"""
    global current_mode
    
    if direction > 0:
        print("Encoder: CW")
        current_mode = (current_mode % 5) + 1
    else:
        print("Encoder: CCW")
        current_mode = 5 if current_mode == 1 else current_mode - 1
    
    display_mode()

def read_encoder():
    """Read rotary encoder value"""
    global encoder_value, last_encoder_value
    
    a = ENC_A.value()
    b = ENC_B.value()
    
    # Simple encoder logic (may need adjustment based on specific encoder)
    if not a:  # A went low
        if not b:
            encoder_value += 1
        else:
            encoder_value -= 1
        
        if encoder_value != last_encoder_value:
            handle_encoder_rotation(encoder_value - last_encoder_value)
            last_encoder_value = encoder_value

def check_buttons():
    """Check all buttons for presses"""
    for button_name, button_pin in button_states.items():
        if button_pin.value() == 0:  # Button pressed (active low)
            time.sleep(debounce_delay / 1000.0)
            if button_pin.value() == 0:
                handle_button_press(button_name)
                # Wait for button release
                while button_pin.value() == 0:
                    time.sleep(0.01)
                time.sleep(debounce_delay / 1000.0)
    
    # Check encoder switch
    if ENC_SW.value() == 0:
        time.sleep(debounce_delay / 1000.0)
        if ENC_SW.value() == 0:
            handle_button_press("ENC_SW")
            while ENC_SW.value() == 0:
                time.sleep(0.01)
            time.sleep(debounce_delay / 1000.0)

def main():
    """Main firmware loop"""
    print("CreatorPad MicroPython Firmware Starting...")
    
    # Initial display
    display.fill(0)
    display.text('CreatorPad', 0, 0)
    display.text('Initializing...', 0, 16)
    display.show()
    time.sleep(2)
    
    display_mode()
    
    print("CreatorPad Firmware Ready")
    
    # Main loop
    while True:
        check_buttons()
        read_encoder()
        time.sleep(0.05)

if __name__ == '__main__':
    main()
