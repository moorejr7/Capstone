int led = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
  delay(100);
  if (analogRead(A0) == 0) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}
