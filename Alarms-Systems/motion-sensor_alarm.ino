// Pin assignments for RGB LED 
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

// Pin for piezo buzzer
const int buzzerPin = 7;

// Button pin 
const int buttonPin = 9;

// PIR motion sensor pin
const int sensor = 8;

// Variable to store motion sensor state
int val = 0;

// Tracks whether the alarm is currently active
bool alarmTriggered = false;

void setup() {
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  pinMode(sensor, INPUT);
  
  Serial.begin(9600);
  Serial.println("System armed...waiting for motion.");
  
}

void loop() {
  // Read the current state of the motion sensor
  val = digitalRead(sensor);

  // If the alarm is NOT currently triggered
  if (!alarmTriggered) {
     
	blinkYellow();// Blink the RGB LED yellow to indicate the system is armed

    if (val == HIGH) {    
      //triggers the alarm if motion is detected
      Serial.println("Motion detected!");
      alarmTriggered = true;
    }
  }
  else {
    //alarm IS currently triggered
    flashRed();
    tone(buzzerPin, 1000); // Play tone at 1000 Hz

    // Check if the button is pressed to deactivate the alarm
    if (digitalRead(buttonPin) == HIGH) {
      // Turn off the buzzer
      noTone(buzzerPin);

      // Reset the alarm state
      alarmTriggered = false;
      Serial.println("Alarm deactivated and system resetting");
      delay(5000);
      Serial.println("System armed...waiting for motion.");

      // Wait until the PIR sensor stops detecting motion before rearming
      while (digitalRead(sensor) == HIGH) {
        delay(100); // Short delay to avoid freezing the system
      }

      delay(1000); // Small delay to prevent bouncing issues
    }
  }
}

// Function to set the RGB LED color
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


void blinkYellow() {
  setColor(255, 255, 0); // Yellow
  delay(500);
  setColor(0, 0, 0);     // LED off
  delay(500);
}

void blinkBlue() {
  setColor(0, 0, 255); // Blue
  delay(500);
  setColor(0, 0, 0);     // LED off
  delay(500);
}

void flashRed() {
  setColor(255, 0, 0); // Red
  delay(200);
  setColor(0, 0, 0);   // LED off
  delay(200);
}



