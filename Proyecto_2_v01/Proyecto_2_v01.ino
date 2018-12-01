int SWITCH = 2;
int RED_A = 5;
int RED_B = 4;
int GREEN = 3;

// Carga inicial del programa
void setup() {
  // Pines de entrada
  pinMode(SWITCH, INPUT);
  // Pines de salida
  pinMode(RED_A, OUTPUT);
  pinMode(RED_B, OUTPUT);
  pinMode(GREEN, OUTPUT);
}


// Bucle principal
void loop() {

  if (digitalRead(SWITCH) == LOW) {
    // Sin pulsar
    digitalWrite(GREEN, LOW);
    digitalWrite(RED_A, HIGH);
    digitalWrite(RED_B, LOW);
    delay(500);
    digitalWrite(RED_A, LOW);
    digitalWrite(RED_B, HIGH);
    delay(500);
  } else {
    // Pulsado
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED_A, HIGH);
    digitalWrite(RED_B, LOW);
    delay(125);
    digitalWrite(RED_A, LOW);
    digitalWrite(RED_B, HIGH);
    delay(125);
  }

}
