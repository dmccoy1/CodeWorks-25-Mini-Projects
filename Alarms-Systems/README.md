 # Arduino Alarm Systems: Motion & Proximity Detection

This project contains **two separate Arduino-based alarm systems** that serve a similar purpose — detecting movement or presence and triggering an alert. Each system uses a different type of sensor to monitor its environment:

* **System A**: PIR Motion Sensor-Based Alarm
* **System B**: Ultrasonic Proximity Sensor-Based Alarm

Both systems feature:

* RGB LED visual feedback
* Buzzer alert system
* Button to deactivate the alarm
* Serial output for real-time monitoring

---

## Shared Components

| Component                   | Quantity |
| --------------------------- | -------- |
| Arduino Uno (or compatible) | 1        |
| RGB LED (common cathode)    | 1        |
| 220Ω Resistors              | 3        |
| Piezo Buzzer                | 1        |
| Push Button                 | 1        |
| Breadboard & Jumper Wires   | -        |

---

## System A: PIR Motion Sensor Alarm

### 🔧 Additional Component:

* PIR Motion Sensor (1 unit)

### Pin Assignments:

| Component         | Arduino Pin |
| ----------------- | ----------- |
| PIR Sensor        | 8           |
| RGB LED (R, G, B) | 3, 5, 6     |
| Buzzer            | 7           |
| Button            | 9           |

### Behavior:

* System blinks yellow (RGB) while armed.
* When motion is detected by the PIR sensor, the system:

  * Flashes red on the RGB LED.
  * Activates the buzzer.
  * Waits for user to press a button to deactivate.
* Once reset, the system waits for no motion before rearming.

---

## System B: Ultrasonic Proximity Sensor Alarm

### Additional Components:

* Ultrasonic Distance Sensor (HC-SR04 or 3-pin variant)

### Pin Assignments:

| Component         | Arduino Pin                           |
| ----------------- | ------------------------------------- |
| Ultrasonic Sensor | Trig: 11, Echo: 12 *(or 3-pin on 11)* |
| RGB LED (R, G, B) | 3, 5, 6                               |
| Buzzer            | 7                                     |
| Button            | 9                                     |

### Behavior:

* System continuously measures distance.
* If an object is detected within **10 inches**, the system:

  * Flashes red on the RGB LED.
  * Activates the buzzer.
* Pressing the button stops the alarm and re-arms once the object is removed from the detection zone.

---

## Serial Monitor Output Example

```
System armed...waiting for motion.
Motion detected!
Alarm triggered.
Alarm deactivated and system resetting
System armed...waiting for motion.
```

```
System armed...waiting for object.
Distance: 13.45 in
Distance: 9.81 in
Object Detected!
Alarm triggered.
Alarm deactivated.
System re-armed.
```
