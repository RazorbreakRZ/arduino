#include <math.h>

#define PIN_PIEZO 				3
#define PIN_SERVO 				5
#define PIN_SONAR_ECHO 		9
#define PIN_SONAR_TRIGGER 10

// PIEZO configuration
#define PIEZO_MIN_FREQ  100       //Buzzer minimum working frequency
#define PIEZO_MAX_FREQ  50000     //Buzzer maximum audible working frequency

// Global vars
long duration = 0;
long distance = 0;


void setup() {  
	makeNoise(5000, 50, 0, 1);
	randomSeed(analogRead(0));
	pinMode(PIN_SONAR_TRIGGER, OUTPUT);
	pinMode(PIN_SONAR_ECHO, INPUT);
	// pinMode(PIN_SERVO, OUTPUT);
	delay(1000);
	makeNoise(5000, 50, 150, 2);
	Serial.begin(9600);
}

void loop() {
	Serial.println(ping());
	//makeNoise(10000, 50, 1000 ,1);
	delay(1000);
}

long ping() {
	digitalWrite(PIN_SONAR_TRIGGER, LOW);
	delayMicroseconds(2);

	digitalWrite(PIN_SONAR_TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_SONAR_TRIGGER, LOW);

	duration = pulseIn(PIN_SONAR_ECHO, HIGH);
	distance = duration * 0.034 / 2;

	return distance;
}

void makeNoise(int frequency, int duration, int wait, int times) {
  for(int i=0; i<times; i++) {
    tone(PIN_PIEZO, frequency, duration);
    delay(wait);
  }
}