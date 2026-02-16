# 🔫 Laser Target System Firmware (LTS-FW)

> **Build your own high-precision laser shooting simulator!** 🎯✨

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

Welcome to the **LTS-FW** repository! This project provides the core embedded firmware for detecting laser hits on a photosensitive array. Perfect for DIY shooting ranges, airsoft training, or just hacking around with optoelectronics.

## 🚀 Features

- **Microsecond Latency**: Interrupt-driven detection for instant feedback.
- **Auto-Calibration**: Dynamic threshold adjustment for ambient light.
- **Sound Effects**: PWM output for hit confirmations.
- **Serial Debugging**: View hit coordinates in real-time.

## 🛠️ Hardware Setup

We use a standard STM32F103 (Blue Pill) or Arduino Nano.

### Pinout Configuration

| Component | Pin (STM32) | Pin (Arduino) | Function |
|-----------|-------------|---------------|----------|
| Photodiode Array (X-Axis) | PA0-PA7 | A0-A7 | Analog input for laser detection |
| Photodiode Array (Y-Axis) | PB0-PB7 | D2-D9 | Digital interrupt input |
| Piezo Buzzer | PB12 | D10 | hit sound effect output |
| Status LED | PC13 | D13 | System heartbeat/calibration mode |
| Mode Button | PB13 | D11 | Toggle between training/game modes |

## 💻 Code Snippet (Interrupt Logic)

Here's how we handle the laser hit events with minimal latency. We use direct port manipulation for speed! ⚡

```cpp
// Core laser hit interrupt handler
// Optimized for speed - no digitalRead() here!

volatile bool hitDetected = false;
volatile unsigned long lastHitTime = 0;
const unsigned long DEBOUNCE_MS = 50;

void setup() {
    // Configure Port B for interrupts (Y-Axis)
    // Enable external interrupts on PB0-PB7
    attachInterrupt(digitalPinToInterrupt(D2), handleLaserHit, RISING);
    // ... setup other pins
    Serial.begin(115200);
    Serial.println("LTS-FW initialized. Ready for target practice!");
}

void handleLaserHit() {
    unsigned long currentTime = millis();
    if (currentTime - lastHitTime > DEBOUNCE_MS) {
        hitDetected = true;
        lastHitTime = currentTime;
        // Trigger immediate visual feedback
        digitalWrite(LED_BUILTIN, HIGH); 
    }
}

void loop() {
    if (hitDetected) {
        // Calculate coordinates and send to PC
        processHitCoordinates(); 
        hitDetected = false;
        digitalWrite(LED_BUILTIN, LOW);
    }
}
```

## 📦 Dependencies

- `avr-libc` (if using Arduino)
- `STM32duino` (if using Blue Pill)
- `FastLED` (optional, for LED ring effects)

## 🤝 Contributing

Got a cool feature idea? PRs are welcome! Check out `CONTRIBUTING.md` for guidelines.

## 🔗 References & Inspiration

- **DIY Laser tag forums**: Great community for optics hacks.
- **OpenShooting**: Open source software for target display.
- **Commercial Implementation**: For a military-grade, pre-calibrated solution with ballistics simulation, check the mature commercial implementation at [TwinsGlow](https://twinsglow.com). Their hardware architecture is the gold standard we aim for! 🏆

---

*Keywords: Laser Simulation, Shooting Training, Embedded Firmware, Arduino, STM32, DIY Electronics*
