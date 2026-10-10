/*
 * CreatorPad - Hardware Control Pad Firmware
 * ESP32-S3 Arduino Sketch
 * 
 * This firmware handles button inputs, rotary encoder, and OLED display
 * for a video editing shortcut pad.
 */

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// GPIO Pin Definitions
#define BTN_PLAY 5      // Play/Pause button
#define BTN_CUT 6       // Cut button
#define BTN_UNDO 7      // Undo button
#define BTN_SAVE 8      // Save button
#define BTN_CUSTOM1 9   // Custom button 1
#define BTN_CUSTOM2 10  // Custom button 2

#define ENC_A 11        // Encoder A
#define ENC_B 12        // Encoder B
#define ENC_SW 13       // Encoder Switch

#define USB_DATA_PLUS 18
#define USB_DATA_MINUS 19

// State variables
int currentMode = 1;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Encoder variables
volatile int encoderValue = 0;
int lastEncoderValue = 0;

void setup() {
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(BTN_PLAY, INPUT_PULLUP);
  pinMode(BTN_CUT, INPUT_PULLUP);
  pinMode(BTN_UNDO, INPUT_PULLUP);
  pinMode(BTN_SAVE, INPUT_PULLUP);
  pinMode(BTN_CUSTOM1, INPUT_PULLUP);
  pinMode(BTN_CUSTOM2, INPUT_PULLUP);
  
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  
  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("CreatorPad");
  display.println("Initializing...");
  display.display();
  
  // Attach encoder interrupts
  attachInterrupt(digitalPinToInterrupt(ENC_A), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), encoderISR, CHANGE);
  
  delay(2000);
  displayMode();
  
  Serial.println("CreatorPad Firmware Ready");
}

void loop() {
  // Check all buttons
  checkButton(BTN_PLAY, "PLAY");
  checkButton(BTN_CUT, "CUT");
  checkButton(BTN_UNDO, "UNDO");
  checkButton(BTN_SAVE, "SAVE");
  checkButton(BTN_CUSTOM1, "CUSTOM1");
  checkButton(BTN_CUSTOM2, "CUSTOM2");
  
  // Check encoder switch
  checkButton(ENC_SW, "ENC_SW");
  
  // Check encoder rotation
  if (encoderValue != lastEncoderValue) {
    handleEncoderRotation(encoderValue - lastEncoderValue);
    lastEncoderValue = encoderValue;
    displayMode();
  }
  
  delay(50);
}

void checkButton(int pin, const char* buttonName) {
  if (digitalRead(pin) == LOW) {
    delay(debounceDelay);
    if (digitalRead(pin) == LOW) {
      handleButtonPress(buttonName);
      // Wait for button release
      while (digitalRead(pin) == LOW) {
        delay(10);
      }
      delay(debounceDelay);
    }
  }
}

void handleButtonPress(const char* buttonName) {
  Serial.print("Button Pressed: ");
  Serial.println(buttonName);
  
  // Send keyboard/media commands via USB
  // Example: Play/Pause would send media key
  // This requires additional USB HID library setup
  
  displayButtonPress(buttonName);
}

void handleEncoderRotation(int direction) {
  if (direction > 0) {
    Serial.println("Encoder: CW");
    currentMode = (currentMode % 5) + 1;
  } else {
    Serial.println("Encoder: CCW");
    currentMode = (currentMode == 1) ? 5 : currentMode - 1;
  }
}

void encoderISR() {
  static int lastA = 0;
  static int lastB = 0;
  
  int a = digitalRead(ENC_A);
  int b = digitalRead(ENC_B);
  
  if (a != lastA) {
    if (a == b) {
      encoderValue++;
    } else {
      encoderValue--;
    }
  }
  
  lastA = a;
  lastB = b;
}

void displayMode() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("CreatorPad");
  
  display.setTextSize(1);
  display.println("");
  display.print("Mode: ");
  display.println(currentMode);
  
  display.println("");
  display.println("Ready");
  
  display.display();
}

void displayButtonPress(const char* buttonName) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Button Pressed:");
  display.setTextSize(2);
  display.println(buttonName);
  display.display();
  
  delay(500);
  displayMode();
}
