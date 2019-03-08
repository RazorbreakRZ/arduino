#include <math.h>

void setup() {  
	randomSeed(analogRead(0));
	Serial.begin(9600);
}

void loop() {
	int data = random(0,255);
	Serial.write(data); // data value must be 0-255
	delay(1000);
}