#include <math.h>
#include <Servo.h>

// PIN declaration
#define PIN_PIEZO			3
#define PIN_SERVO			5
#define PIN_SWITCH_MASTER	6
#define PIN_SWITCH_AUTO		7
#define PIN_SONAR_ECHO		9
#define PIN_SONAR_TRIGGER	10

// SERVO configuration
#define SERVO_MIN_ANGLE			0	//Servo minimun angle value
#define SERVO_CENTER_ANGLE		90	//Servo angle centered
#define SERVO_MAX_ANGLE			180	//Servo maximun angle value
#define SERVO_STEP				1	//Servo step size (in degrees)
#define SERVO_START_POSITION	0	//Servo start angle

// PIEZO configuration
#define PIEZO_MIN_FREQ  100		//Buzzer minimun working frequency
#define PIEZO_MAX_FREQ  50000	//Buzzer maximun audible working frequency

// Switches
boolean switchMaster = false;
boolean lastMasterState = false;
boolean switchAuto = false;
boolean lastAutoState = false;

// Controllers
boolean turnLeft = false;
boolean turnRight = false;

// Buttons
boolean buttonFire1 = false;
boolean buttonFire2 = false;
boolean buttonFire3 = false;
boolean buttonFire4 = false;

// Global vars
Servo myServo;

// State vars
boolean servoDirection = 1; // 0:left 1:right

// Data vars
byte flags = 0;
int angle = 0;
int lastAngle = 0;
int distance = 0;
int lastDistance = 0;


// Initial function
void setup() {  
	doNoise(5000, 50, 150, 1);
	Serial.begin(9600);
	randomSeed(analogRead(0));
	pinMode(PIN_SWITCH_MASTER, INPUT);
	pinMode(PIN_SWITCH_AUTO, INPUT);
	pinMode(PIN_SONAR_TRIGGER, OUTPUT);
	pinMode(PIN_SONAR_ECHO, INPUT);
	myServo.attach(PIN_SERVO);
	servoResetPosition();
	doNoise(5000, 50, 150, 2);
}

// Main loop
void loop() {
	updateCurrentStatus();
	checkChanges();
	if(switchMaster) {
		// MASTER on
		if(switchAuto) {
			// AUTO mode
			doStep();
			updateServoAngle();
		} else {
			// MANUAL mode
			doStep();
			// TODO: implement here manual control
		}
	} else {
		// MASTER off
		startPosition();
		sendSerialData();
	}
}

void updateCurrentStatus() {
	// Save last status before change
	lastMasterState = switchMaster;
	lastAutoState = switchAuto;
	// Read and save current status
	switchMaster = digitalRead(PIN_SWITCH_MASTER);
	switchAuto = digitalRead(PIN_SWITCH_AUTO);
}

void checkChanges() {
	// Set SERVO to position 0 if MASTER change its status to ON
	if(switchMaster && !lastMasterState) {
		setServoAngle(SERVO_MIN_ANGLE);
	}
}

void servoStartPosition() {
	setServoAngle(SERVO_MIN_ANGLE);
	lastAngle = SERVO_MIN_ANGLE;
}

void servoResetPosition() {
	setServoAngle(SERVO_CENTER_ANGLE);
	lastAngle = SERVO_CENTER_ANGLE;
}

void doStep() {
	setServoAngle(angle)
	delay(30);
	doPulse()
	sendSerialData();
}

void sendSerialData() {
	Serial.print(flags);
	Serial.print(':');
	Serial.print(angle);
	Serial.print(':');
	Serial.print(distance);
	Serial.print('.');
}

void updateServoAngle() {
	if(servoDirection) {
		servoAngle += SERVO_STEP;
	} else {
		servoAngle -= SERVO_STEP;
	}
	if(angle <= SERVO_MIN_ANGLE) {
		angle = SERVO_MIN_ANGLE;
		servoDirection = 1;
	} else if(angle >= SERVO_MAX_ANGLE) {
		angle = SERVO_MAX_ANGLE;
		servoDirection = 0;
	}
}

void setServoAngle(int newAngle) {
	myServo.write(newAngle);
	lastAngle = angle;
	angle = newAngle;
}

void doPulse() {
	long duration = 0;
	digitalWrite(PIN_SONAR_TRIGGER, LOW);
	delayMicroseconds(2);
	digitalWrite(PIN_SONAR_TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_SONAR_TRIGGER, LOW);
	duration = pulseIn(PIN_SONAR_ECHO, HIGH);
	lastDistance = distance
	distance = duration * 0.034 / 2;
}

void doNoise(int frequency, int duration, int wait, int times) {
	for(int i=0; i<times; i++) {
		tone(PIN_PIEZO, frequency, duration);
		if(wait > 0) {
			delay(wait);
		}
  	}
}