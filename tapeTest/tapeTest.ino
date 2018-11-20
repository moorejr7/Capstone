float eTapePin = A5;
float sensorValue1 = 0;
float sensorValue2 = 0;
float sensorValue3 = 0;
float sensorValue4 = 0;
float sensorValue5 = 0;
float voltage = 0;
float height = 0;
float kiloOhms = 0;
float volume = 0;

void setup() {
  Serial.begin(9600);
}

float measureVolume() {
  float sensorValue1 = 0;
  float sensorValue2 = 0;
  float sensorValue3 = 0;
  float sensorValue4 = 0;
  float sensorValue5 = 0;
  float voltage = 0;
  float height = 0;
  float kiloOhms = 0;
  
  sensorValue1 = analogRead(eTapePin);
  sensorValue2 = analogRead(eTapePin);
  sensorValue3 = analogRead(eTapePin);
  sensorValue4 = analogRead(eTapePin);
  sensorValue5 = analogRead(eTapePin);
  voltage = (sensorValue1 + sensorValue2 + sensorValue3 + sensorValue4 + sensorValue5) / 5;
  
  kiloOhms = voltage / 1000;

  height = (kiloOhms - 2.2) / (-0.14);

  return(3.14 * (1.75 * 1.75) * height) * 16.387;
}
