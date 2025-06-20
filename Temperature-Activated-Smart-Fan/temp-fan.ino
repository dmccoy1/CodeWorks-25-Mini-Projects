// Pin configuration
const int buttonPin = 2;      // Button connected to digital pin 2
const int motorPin = 9;       // Transistor base connected to digital pin 9 (with PWM)
const int ledPin = 13;        // LED connected to digital pin 13
const int tempPin = A0;      // TMP36 sensor connected to analog pin A0

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Read temperature from TMP36
  int sensorValue = analogRead(tempPin);
  
  // Convert to voltage
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Convert voltage to temperature in C
  float temperatureC = (voltage - 0.5) * 100;

  // Convert C to F
  float temperatureF = (temperatureC * 9.0/5.0) + 32;

  Serial.print("Temperature (F): ");
  Serial.println(temperatureF);

  // Check if temp is above or equal to 85 and button is pressed
  if (temperatureF >= 75.0) {
    digitalWrite(ledPin, HIGH);
    if (digitalRead(buttonPin) == HIGH) {
      // Ramp up motor speed
      for (int speed = 0; speed <= 50; speed++) {
        analogWrite(motorPin, speed);
        delay(50);
      }
      // Ramp down motor speed
      for (int speed = 50; speed >= 0; speed--) {
        analogWrite(motorPin, speed);
        delay(50);
      }
    }
  } else {
    digitalWrite(ledPin, LOW);
    analogWrite(motorPin, 0);
  }

  delay(500);
}

