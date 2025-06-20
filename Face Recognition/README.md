# Smart Face Recognition Door Lock System

This project is a smart door lock system that combines facial recognition AI with physical computing. It uses a **Raspberry Pi** for real-time face detection and recognition with **OpenCV** and the `face_recognition` Python library. Upon recognizing an authorized user, the Raspberry Pi sends a serial signal to an **Arduino**, which unlocks the door using a servo motor and provides feedback via RGB LED and a buzzer.

---

## Project Goals

* Combine AI-powered facial recognition with physical hardware interaction
* Build a working smart security system prototype
* Explore cross-platform communication between Raspberry Pi and Arduino

---

##  How It Works

### 1. **Training the AI**

Use the `image_capture.py` script to take pictures of the user:

```bash
python3 image_capture.py
```

Captured images are saved in the `dataset/` folder, organized by name. These are used to train the 

### 2. **Encoding Faces**

The Facial Recognition model is trained by running `model_training.py` which encodes the captured faces and saves them to `encodings.pickle` for use by the recognition system.

### 3. **Real-Time Face Recognition**

The Raspberry Pi runs `facial_recognition_hardware.py`, which:

* Loads trained encodings
* Uses the PiCamera2 to capture live video
* Detects and recognizes faces in real time
* Sends `'pass\n'` or `'fail\n'` over serial to Arduino

### 4. **Arduino Door Control**

The Arduino listens to the serial port and responds accordingly:

* `'pass'`: Unlocks the door (servo turns), green LED, plays success chime
* `'fail'`: Stays locked, red LED, plays warning buzz

---

## Hardware Used

* Raspberry Pi 4 with PiCamera (or compatible Pi with USB cam)
* Arduino Uno
* Servo motor
* RGB LED (or 3 separate LEDs)
* Piezo buzzer
* USB cable for serial communication

---

## Arduino Code Overview

```cpp
#include <Servo.h>
...
if (command == "pass") {
  handlePass(); // Green LED, unlock, chime
} else if (command == "fail") {
  handleFail(); // Red LED, lock, buzz
}
```

### Feedback Functions:

* **Green LED + Servo unlock + Chime** for authorized
* **Red LED + Lock + Buzz** for unauthorized

---

## Raspberry Pi Python Code Overview

Main script: [`facial_recognition_hardware.py`](facial_recognition_hardware.py)

* Uses `face_recognition`, `OpenCV`, and `picamera2`
* Matches faces in the camera feed to authorized encodings
* Communicates with Arduino over `/dev/ttyUSB0` using `pyserial`

Training image capture script: [`image_capture.py`](image_capture.py)

---

## Getting Started

### Raspberry Pi Setup:

1. Install dependencies:

```bash
pip3 install face_recognition opencv-python picamera2 imutils pyserial
```

2. Capture training images:

```bash
python3 image_capture.py
```

3. Run facial recognition:

```bash
python3 facial_recognition_hardware.py
```

### Arduino Setup:

1. Upload the Arduino sketch via the Arduino IDE
2. Connect via USB to the Raspberry Pi
3. Ensure `Serial.begin(9600)` matches Python serial settings

Based on this guide:
[Face Recognition with Raspberry Pi and OpenCV – Core Electronics](https://core-electronics.com.au/guides/raspberry-pi/face-recognition-with-raspberry-pi-and-opencv/)
