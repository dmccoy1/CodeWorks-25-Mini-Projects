# Color-Changing Mood Light

A responsive Arduino-based mood light that automatically adjusts its colors and brightness based on the ambient light in the room. As the surroundings grow darker, the mood light gently fades in and cycles smoothly through glowing colors, creating a soothing atmosphere.

---

## Features

- Automatically senses ambient light using an LDR (Light Dependent Resistor)
- Adjusts LED brightness inversely to room brightness (darker room = brighter LEDs)
- Smoothly fades through colors: red → green → blue, continuously cycling
- Uses two RGB LEDs for a unified glowing effect

---

## Components Used

| Component            | Description                              |
|----------------------|------------------------------------------|
| Arduino Uno          | Microcontroller running the program      |
| 2 × RGB LEDs         | Produce the color-changing light effect  |
| LDR (Light-Dependent Resistor) | Senses ambient light levels          |
| Resistors            | Protect components from damage:          |
|                      | - 2 × 220Ω for each RGB LED pin          |
|                      | - 1 × 10KΩ for LDR voltage divider       |
| Breadboard + Jumper Wires | For circuit assembly                  |

---

<img width="777" alt="Screenshot 2025-06-20 at 1 11 06 PM" src="https://github.com/user-attachments/assets/97680821-39b8-4560-bc95-f5bab3b4ee1c" />

## How It Works

1. The LDR reads the ambient light level and sends a value to the Arduino.
2. Arduino maps this sensor reading to control LED brightness inversely — the darker the room, the brighter the LEDs glow.
3. RGB LEDs cycle through a smooth transition of colors: red → green → blue.
4. The brightness of the LEDs is adjusted in real-time according to ambient light for a natural glowing effect.
5. Two main functions:
   - `fadeColors()` smoothly transitions between colors.
   - `setColor()` updates both RGB LEDs simultaneously.

---

