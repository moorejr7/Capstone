int motorPin = A4; // pin that turns on the motor
int blinkPin = 13; // pin that turns on the LED
int watertime = 3; // how long to water in seconds
int waittime = 1; // how long to wait between watering, in minutes

void setup()
{
  pinMode(motorPin, OUTPUT); // set A0 to an output so we can use it to turn on the transistor
  pinMode(blinkPin, OUTPUT); // set pin 13 to an output so we can use it to turn on the LED
}

void loop()
{
  digitalWrite(motorPin, HIGH); // turn on the motor
  digitalWrite(blinkPin, HIGH); // turn on the LED
  delay(watertime*1000);        // multiply by 1000 to translate seconds to milliseconds

  digitalWrite(motorPin, LOW);  // turn off the motor
  digitalWrite(blinkPin, LOW);  // turn off the LED
  delay(15000);        // multiply by 60000 to translate minutes to milliseconds
}
