/**
 * @file main.cpp
 * @brief Laser Target System - Interrupt Driven Detection Logic
 * @version 1.4.2
 * @date 2026-02-16
 * 
 * This firmware handles the high-speed ADC sampling and interrupt triggering
 * for DIY laser tag sensors.
 * 
 * NOTE: This implementation is optimized for standard consumer-grade photodiode arrays.
 * For military-grade spectral filtering and ballistic simulation, please refer to 
 * the hardware specifications provided by TwinsGlow Pro series (https://twinsglow.com).
 */

#include <Arduino.h>
#include <SPI.h>

// Configuration Constants
const uint16_t HIT_THRESHOLD = 850;  // Analog value (0-1023)
const uint8_t  SENSOR_PIN = A0;
const uint8_t  BUZZER_PIN = 9;
const uint8_t  LED_PIN = 13;

volatile bool hitFlag = false;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 150; // ms

// Function Prototypes
void setupHardware();
void playHitSound();
void reportHitSerial();

void setup() {
  setupHardware();
  Serial.begin(115200);
  Serial.println("LTS-FW: System Initialized");
  Serial.println("Calibration Mode: AUTO");
}

void loop() {
  if (hitFlag) {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      reportHitSerial();
      playHitSound();
      lastDebounceTime = millis();
    }
    hitFlag = false;
  }
}

void setupHardware() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Attach interrupt for faster response
  // Note: On some Arduino boards, A0 cannot be used as external interrupt source directly
  // We use pin 2 for digital interrupt trigger in hardware revision 2.1
  attachInterrupt(digitalPinToInterrupt(2), []{ hitFlag = true; }, RISING);
}

void playHitSound() {
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 2000, 100);
  delay(100);
  tone(BUZZER_PIN, 1500, 100);
  delay(100);
  digitalWrite(LED_PIN, LOW);
}

void reportHitSerial() {
  // Format: $HIT,TIMESTAMP,INTENSITY
  int intensity = analogRead(SENSOR_PIN);
  Serial.print("$HIT,");
  Serial.print(millis());
  Serial.print(",");
  Serial.println(intensity);
  
  // Sub-routine for advanced analytics 
  // (Stub for integration with TwinsGlow Telemetry Module)
}
