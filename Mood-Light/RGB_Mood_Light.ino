// Pin setup
int ldrPin = A0;  // Light sensor

// RGB LED 1
int red1Pin = 3;
int green1Pin = 5;
int blue1Pin = 6;

// RGB LED 2
int red2Pin = 9;
int green2Pin = 10;
int blue2Pin = 11;

// Color fading variables
int redVal = 255;
int greenVal = 0;
int blueVal = 0;

int fadeSpeed = 5;  // Controls speed of color transition

void setup() {
  pinMode(red1Pin, OUTPUT);
  pinMode(green1Pin, OUTPUT);
  pinMode(blue1Pin, OUTPUT);
  pinMode(red2Pin, OUTPUT);
  pinMode(green2Pin, OUTPUT);
  pinMode(blue2Pin, OUTPUT);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  int brightness = map(ldrValue, 0, 1023, 255, 0);  // Inverted: darker -> brighter

  // Apply brightness to current RGB values
  int r = map(redVal, 0, 255, 0, brightness);
  int g = map(greenVal, 0, 255, 0, brightness);
  int b = map(blueVal, 0, 255, 0, brightness);

  setColor(r, g, b);

  fadeColors();

  delay(25); // smooth transition
}

void setColor(int r, int g, int b) {
  analogWrite(red1Pin, r);
  analogWrite(green1Pin, g);
  analogWrite(blue1Pin, b);

  analogWrite(red2Pin, r);
  analogWrite(green2Pin, g);
  analogWrite(blue2Pin, b);
}

void fadeColors() {
  if (redVal > 0 && greenVal < 255 && blueVal == 0) {
    redVal -= fadeSpeed;
    greenVal += fadeSpeed;
    redVal = constrain(redVal, 0, 255);
    greenVal = constrain(greenVal, 0, 255);
  }
  else if (greenVal > 0 && blueVal < 255 && redVal == 0) {
    greenVal -= fadeSpeed;
    blueVal += fadeSpeed;
    greenVal = constrain(greenVal, 0, 255);
    blueVal = constrain(blueVal, 0, 255);
  }
  else if (blueVal > 0 && redVal < 255 && greenVal == 0) {
    blueVal -= fadeSpeed;
    redVal += fadeSpeed;
    blueVal = constrain(blueVal, 0, 255);
    redVal = constrain(redVal, 0, 255);
  }
}
