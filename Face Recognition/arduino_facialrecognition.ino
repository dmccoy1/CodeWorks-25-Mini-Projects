#include <Servo.h>

const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int buzzerPin = 7;
const int servoPin = 2;

Servo doorServo;

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  doorServo.attach(servoPin);
  doorServo.write(0); // Start in locked position
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    if (command == "pass") {
      handlePass();
    } 
    else if (command == "fail") {
      handleFail();
    }
  }
}

void handlePass() {
  setColor(0, 255, 0);    // Green LED
  doorServo.write(90);    // Unlock
  playPositiveChime();
  delay(5000);            
  doorServo.write(0);     // Lock again
  setColor(0, 0, 0);      // LED off
}

void handleFail() {
  setColor(255, 0, 0);    // Red LED
  doorServo.write(0);     // Ensure it's locked
  playNegativeChime();
  delay(3000);
  setColor(0, 0, 0);      // LED off
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void playPositiveChime() {
  tone(buzzerPin, 880, 200);  // A5
  delay(250);
  tone(buzzerPin, 988, 200);  // B5
  delay(250);
  tone(buzzerPin, 1047, 300); // C6
  delay(350);
  noTone(buzzerPin);
}

void playNegativeChime() {
  tone(buzzerPin, 300, 300);  // Low buzz
  delay(350);
  tone(buzzerPin, 200, 300);  // Lower buzz
  delay(350);
  noTone(buzzerPin);
}
