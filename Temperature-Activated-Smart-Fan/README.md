# Smart Temperature-Controlled Fan System

## Project Overview

This project is a **smart automation system** designed to control a DC fan based on real-time temperature data using an **Arduino Uno** and a **TMP36 temperature sensor**. It’s ideal for smart homes, server rooms, greenhouses, or any environment where maintaining optimal temperature is important for comfort, safety, or energy efficiency.

When the temperature rises above a threshold (75°F), an indicator LED lights up. If a button is pressed while the temperature is high, the system ramps up the fan gradually using **Pulse-Width Modulation (PWM)**, then slows it down — simulating an active cooling cycle.

---

## Components Used

* Arduino Uno
* TMP36 Temperature Sensor
* NPN Transistor (e.g., 2N2222 or TIP120)
* DC Fan (or motor)
* Pushbutton
* 220Ω Resistor (for button)
* LED (status indicator)
* Breadboard and jumper wires
* External power supply (if required for fan)

---

##  Pin Configuration

| Component    | Arduino Pin |
| ------------ | ----------- |
| TMP36 Sensor | A0          |
| Button       | D2          |
| DC Fan       | D9 (PWM)    |
| Status LED   | D13         |

---

## How It Works

1. The TMP36 sensor reads ambient temperature.
2. The Arduino converts the analog signal to Fahrenheit.
3. If the temperature ≥ 75°F:

   * The LED turns on.
   * If the button is pressed, the fan speed ramps up and then down using PWM.
4. If the temperature is below 75°F:

   * The LED turns off.
   * The fan remains off.


```cpp
int sensorValue = analogRead(tempPin);
float voltage = sensorValue * (5.0 / 1023.0);
float temperatureC = (voltage - 0.5) * 100;
float temperatureF = (temperatureC * 9.0/5.0) + 32;
```

The code reads and converts the temperature, then uses conditionals and `analogWrite()` to control fan speed based on environmental conditions and button input.
