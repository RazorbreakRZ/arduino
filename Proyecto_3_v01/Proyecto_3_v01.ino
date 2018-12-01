const int RED_A = 5;
const int RED_B = 4;
const int RED_C = 3;
const int TEMPERATURE = A0;
float sensorValue = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Bits por segundo de comunicacion con PC
  for (int pinNumber = 3; pinNumber <= 5 ; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(TEMPERATURE);
  Serial.print(sensorValue);
  Serial.println();

  if (sensorValue >= 157.0) {
    digitalWrite(RED_C, HIGH);
  } else {
    digitalWrite(RED_C, LOW);
  }
  if (sensorValue >= 159.0) {
    digitalWrite(RED_B, HIGH);
  } else {
    digitalWrite(RED_B, LOW);
  }
  if (sensorValue >= 161.0) {
    digitalWrite(RED_A, HIGH);
  } else {
    digitalWrite(RED_A, LOW);
  }
}
