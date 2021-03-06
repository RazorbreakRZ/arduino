#include <math.h>
#include <Servo.h>

// SERVO configuration
const int PIN_SERVOS[] 			= { 5, 6 };
const int SERVO_MIN_ANGLE 		= 45;	//Servo minimun angle value
const int SERVO_CENTER_ANGLE 	= 90;	//Servo angle centered
const int SERVO_MAX_ANGLE 		= 135;	//Servo maximun angle value
const int SERVO_STEP_ANGLE 		= 15;	//Servo step size (in degrees)
const int SERVO_STEP_DELAY		= 100;	//Servo step delay (in ms)
const int SERVO_START_POSITION 	= 0;	//Servo start angle
bool servoDirection 			= 1;	// 0:left 1:right
int servoAngle					= 0;
int lastServoAngle				= 0;
Servo servos[2];

// SONAR configuration
const int PIN_SONAR_TRIGGER 	= 8;
const int PIN_SONAR_ECHO 		= 9;
int distance 					= 0;
int lastDistance 				= 0;

// PIEZO configuration
const int PIN_PIEZO 			= 4;
const int PIEZO_MIN_FREQ 		= 100;		//Buzzer minimun working frequency
const int PIEZO_MAX_FREQ 		= 50000;	//Buzzer maximun audible working frequency

// Switches
const int PIN_SWITCH_MASTER 	= 2;
bool switchMaster 				= false;
bool lastMasterState 			= false;
const int PIN_SWITCH_AUTO 		= 3;
bool switchAuto 				= false;
bool lastAutoState 				= false;

// Controllers
const int PIN_BUTTON_LEFT 		= 8;
bool turnLeft 					= false;
const int PIN_BUTTON_RIGHT 		= 9;
bool turnRight 					= false;

// Launchers
const int PIN_LAUNCHERS[] 		= { 10, 11, 12, 13 };
bool enabledLaunchers[] 		= { false, false, false, false };

// Data
bool debug = false;
byte flags = 0;


// Initial function
void setup() {
  doNoise(5000, 50, 150, 1);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(PIN_SWITCH_MASTER, INPUT);
  pinMode(PIN_SWITCH_AUTO, INPUT);
  servos[0].attach(PIN_SERVOS[0]);
  servos[1].attach(PIN_SERVOS[1]);
  pinMode(PIN_SONAR_TRIGGER, OUTPUT);
  pinMode(PIN_SONAR_ECHO, INPUT);
  pinMode(PIN_BUTTON_LEFT, INPUT);
  pinMode(PIN_BUTTON_RIGHT, INPUT);
  configureLaunchers();
  doNoise(5000, 50, 150, 2);
}

// Main loop
void loop() {
  updateCurrentStatus();
  checkChanges();
  if (switchMaster) {
    // MASTER on
    if (switchAuto) {
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
    servoResetPosition();
    sendSerialData();
  }
}

void updateCurrentStatus() {
  // Save last status before change
  lastMasterState = switchMaster;
  lastAutoState = switchAuto;
  // Read and save current status
  switchMaster = debug || digitalRead(PIN_SWITCH_MASTER);
  switchAuto = debug || digitalRead(PIN_SWITCH_AUTO);
}

void checkChanges() {
  // Set SERVO to position 0 if MASTER change its status to ON
  if (switchMaster && !lastMasterState) {
    setServoAngle(SERVO_MIN_ANGLE);
  }
  if (!switchMaster) {
    distance = 0;
  }
}

void configureLaunchers() {
  pinMode(PIN_LAUNCHERS[0], OUTPUT);
  pinMode(PIN_LAUNCHERS[1], OUTPUT);
  pinMode(PIN_LAUNCHERS[2], OUTPUT);
  pinMode(PIN_LAUNCHERS[3], OUTPUT);
  digitalWrite(PIN_LAUNCHERS[0], enabledLaunchers[0]);
  digitalWrite(PIN_LAUNCHERS[1], enabledLaunchers[1]);
  digitalWrite(PIN_LAUNCHERS[2], enabledLaunchers[2]);
  digitalWrite(PIN_LAUNCHERS[3], enabledLaunchers[3]);
}

void servoStartPosition() {
  setServoAngle(SERVO_MIN_ANGLE);
  lastServoAngle = SERVO_MIN_ANGLE;
}

void servoResetPosition() {
  setServoAngle(SERVO_CENTER_ANGLE);
  lastServoAngle = SERVO_CENTER_ANGLE;
}

void doStep() {
  setServoAngle(servoAngle);
  delay(SERVO_STEP_DELAY);
  doSonarPulse();
  sendSerialData();
}

void sendSerialData() {
  Serial.print("[");
  Serial.print(servoAngle);
  Serial.print(',');
  Serial.print(distance);
  Serial.print(']');
}

void updateServoAngle() {
  if (servoDirection) {
    servoAngle = servoAngle + SERVO_STEP_ANGLE;
  } else {
    servoAngle = servoAngle - SERVO_STEP_ANGLE;
  }
  if (servoAngle <= SERVO_MIN_ANGLE) {
    servoAngle = SERVO_MIN_ANGLE;
    servoDirection = 1;
  } else if (servoAngle >= SERVO_MAX_ANGLE) {
    servoAngle = SERVO_MAX_ANGLE;
    servoDirection = 0;
  }
}

void setServoAngle(int newServoAngle) {
  if (lastServoAngle != newServoAngle) {
    servos[0].write(newServoAngle);
    servos[1].write(newServoAngle);
    lastServoAngle = servoAngle;
    servoAngle = newServoAngle;
  }
}

void doSonarPulse() {
  long duration = 0;
  digitalWrite(PIN_SONAR_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SONAR_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_SONAR_TRIGGER, LOW);
  duration = pulseIn(PIN_SONAR_ECHO, HIGH);
  lastDistance = distance;
  distance = duration * 0.034 / 2;
}

void doNoise(int frequency, int duration, int wait, int times) {
  for (int i = 0; i < times; i++) {
    tone(PIN_PIEZO, frequency, duration);
    if (wait > 0) {
      delay(wait);
    }
  }
}
