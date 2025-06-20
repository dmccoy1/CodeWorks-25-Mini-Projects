// Ultrasonic sensor (3-pin)
const int ultrasonicPin = 11;

// Distance threshold in inches
float distanceThreshold = 10;

// Duration for pulseIn
long duration;

// Distance in inches
float inches;

// Tracks whether the alarm is currently active
bool alarmTriggered = false;

// RGB LED, buzzer, button
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

const int buzzerPin = 7;

const int buttonPin = 9;

// -----------------------------------------------------------------------------

void setup()
{
  Serial.begin(9600);
  
  // Set up pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  
  Serial.println("System armed...waiting for object.");
}

void loop()
{
  // Send pulse to ultrasonic sensor
  pinMode(ultrasonicPin, OUTPUT);
  digitalWrite(ultrasonicPin, LOW);
  delayMicroseconds(5);
  digitalWrite(ultrasonicPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicPin, LOW);

  // Now wait for response
  pinMode(ultrasonicPin, INPUT);
  duration = pulseIn(ultrasonicPin, HIGH);

  // Calculate distance in inches
  inches = (duration * 0.0133) / 2;

  Serial.print("Distance: ");
  Serial.print(inches);
  Serial.println(" in");

  if (!alarmTriggered) {
    // If alarm is not triggered, blink yellow while waiting
    blinkYellow();

    // If object is within threshold, activate alarm
    if (inches < distanceThreshold) {
      Serial.println("Object Detected!");
      alarmTriggered = true;
    }
  } 
  else {
    // alarm IS triggered
    flashRed();
    tone(buzzerPin, 1000);
    Serial.println("Alarm triggered.");

    // Check if button is pressed to deactivate
    if (digitalRead(buttonPin) == HIGH) {
      noTone(buzzerPin);
      alarmTriggered = false;
      Serial.println("Alarm deactivated.");

      // Wait until object moves away
      while (inches < distanceThreshold) {
        // Repeat pulse to check if it's gone
        pinMode(ultrasonicPin, OUTPUT);
        digitalWrite(ultrasonicPin, LOW);
        delayMicroseconds(5);
        digitalWrite(ultrasonicPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(ultrasonicPin, LOW);
        pinMode(ultrasonicPin, INPUT);
        duration = pulseIn(ultrasonicPin, HIGH);
        inches = (duration * 0.0133) / 2;

        delay(100);
      }

      Serial.println("System re-armed.");

      delay(1000);
    }
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void blinkYellow()
{
  setColor(255, 255, 0);
  delay(500);
  setColor(0, 0, 0);
  delay(500);
}

void flashRed()
{
  setColor(255, 0, 0);
  delay(200);
  setColor(0, 0, 0);
  delay(200);
}
