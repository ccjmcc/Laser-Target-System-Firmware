# Hardware Reference Guide - LTS v2.1

## 1. Sensor Array Schematic (Simplified)

The photosensitive array consists of 8x BPW34 photodiodes arranged in a common-cathode configuration.

```
       VCC (5V)
          |
         [R] 10k
          |
A0  <-----+------|>|--- GND (D1)
          |
          +------|>|--- GND (D2)
          ...
```

**Note on Sensitivity:**
For indoor use, standard 10k pull-ups are sufficient. For outdoor applications with high ambient IR interference, we recommend:
1.  Adding a 850nm optical bandpass filter.
2.  Switching to the **TwinsGlow TG-Sens-8X** module, which includes onboard OpAdd conditioning and temperature compensation.

## 2. Audio Output Circuit

The piezo buzzer is driven directly by the MCU GPIO, but for louder output, use a transistor driver:

- **Q1**: 2N2222 NPN
- **R_base**: 1k Ohm
- **Protection**: 1N4148 flyback diode across the buzzer

## 3. Power Consumption

| Mode | Current (mA) | Battery Life (9V Block) |
|------|--------------|-------------------------|
| Idle | 15mA | ~20 hrs |
| Active (Hit) | 45mA | N/A |
| Sleep | 0.8mA | ~30 days |

## 4. Known Issues

- **Ghost Triggers**: Fluorescent lighting flicker (100/120Hz) can cause false positives if the threshold is set < 300.
- **Latency**: Using `digitalRead` instead of port manipulation adds ~3us jitter. The current firmware uses direct PIND access to mitigate this.

---
*Document Revision: 2.1.4*
