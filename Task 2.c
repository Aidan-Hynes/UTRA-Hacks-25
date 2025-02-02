#include <NewPing.h>


#define LMotorC2 1
#define LMotorC1 2
#define RMotorC2 3
#define RMotorC1 4

#define LMotorPWM 5
#define RMotorPWM 6

#define UltraTrig 8
#define UltraEcho 9

#define ServoPWM 11

#define LED 13

#define ColourOut A0
#define ColourS0 A1
#define ColourS1 A2
#define ColourS3 A3
#define ColourS2 A4


NewPing sonar(UltraTrig, UltraEcho, 400);


int redMin = 193; // Red minimum value
int redMax = 1353; // Red maximum value
int greenMin = 276; // Green minimum value
int greenMax = 1527; // Green maximum value
int blueMin = 240; // Blue minimum value
int blueMax = 1117; // Blue maximum value


void setup() {
  Serial.begin(9600);
  pinMode(LMotorC2, OUTPUT);
  pinMode(LMotorC1, OUTPUT);
  pinMode(RMotorC2, OUTPUT);
  pinMode(RMotorC1, OUTPUT);

  pinMode(LMotorPWM, OUTPUT);
  pinMode(RMotorPWM, OUTPUT);

  pinMode(ServoPWM, OUTPUT);

  pinMode(LED, OUTPUT);

  pinMode(ColourOut, INPUT);

  pinMode(ColourS0, OUTPUT);
  pinMode(ColourS1, OUTPUT);
  pinMode(ColourS3, OUTPUT);
  pinMode(ColourS2, OUTPUT);


	digitalWrite(ColourS0,HIGH);
	digitalWrite(ColourS1,LOW);
}

void loop() {

  servoMove(0);

  motorMoveBoth(true, 127);
  unsigned int distance = 200;
  
  while(distance >= 20) {
    delay(50);
    distance = sonar.ping_cm();
    Serial.println(distance);
  }

  motorBreak(true);

  int redValue = getRedValue();
  delay(200);
  int greenValue = getGreenValue();
  delay(200);
  int blueValue = getBlueValue();
  delay(200);

  // Print output to Serial Monitor
	Serial.print(" Red = ");
	Serial.print(redValue);
	Serial.print(" - Green = ");
	Serial.print(greenValue);
	Serial.print(" - Blue = ");
	Serial.println(blueValue);

  delay(1000);

  if(redValue <= 100 && greenValue <= 100 && blueValue <= 100) {
    motorBreak(true);
    while(1){}
  }
  else if(redValue >= 150 && redValue >= greenValue && redValue >= blueValue) {
    motorTankTurn(true, 127);
    delay(3000);
  }
  else if(greenValue >= 150 && greenValue >= redValue && greenValue >= blueValue) {
    motorTankTurn(true, 127);
    delay(1500);
  }
  else if(blueValue >= 150 && blueValue >= redValue && blueValue >= greenValue) {
    motorTankTurn(false, 127);
    delay(1500);
  }
}

void motorMoveLeft(bool forward, int speed) {
    analogWrite(LMotorPWM, speed);

    if(forward) {
      digitalWrite(LMotorC1, HIGH);
      digitalWrite(LMotorC2, LOW);
    }
    else {
      digitalWrite(LMotorC1, LOW);
      digitalWrite(LMotorC2, HIGH);
    }
}

void motorMoveRight(bool forward, int speed) {
    analogWrite(RMotorPWM, speed);

    if(forward) {
      digitalWrite(RMotorC1, HIGH);
      digitalWrite(RMotorC2, LOW);
    }
    else {
      digitalWrite(RMotorC1, LOW);
      digitalWrite(RMotorC2, HIGH);
    }
}

void motorMoveBoth(bool forward, int speed) {
  motorMoveLeft(forward, speed);
  motorMoveRight(forward, speed);
}

void motorTankTurn(bool clockwise, int speed) {
  if(clockwise) {
    motorMoveLeft(true, speed);
    motorMoveRight(false, speed);
  }
  else {
    motorMoveLeft(false, speed);
    motorMoveRight(true, speed);
  }
}

void motorBreak(bool motor_break) {
  if(motor_break) {
    digitalWrite(LMotorC1, HIGH);
    digitalWrite(LMotorC2, HIGH);
    digitalWrite(RMotorC1, HIGH);
    digitalWrite(RMotorC2, HIGH);
  }
  else {
    digitalWrite(LMotorC1, LOW);
    digitalWrite(LMotorC2, LOW);
    digitalWrite(RMotorC1, LOW);
    digitalWrite(RMotorC2, LOW);
  }
}

void servoMove(long angle) {
  long pulse_width = map(angle, 0, 180, 1000, 2500);
  digitalWrite(ServoPWM, HIGH);
  delay(pulse_width/1000);
  digitalWrite(ServoPWM, LOW);
  delay(20 - (pulse_width/1000));
}



// Function to read Red Pulse Widths
int getRedValue() {
	// Set sensor to read Red only
	digitalWrite(ColourS2,LOW);
	digitalWrite(ColourS3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(ColourOut, LOW);
  int rgb_value = map(PW, redMin, redMax, 255, 0); 

	return rgb_value;
}

// Function to read Green Pulse Widths
int getGreenValue() {
	// Set sensor to read Green only
	digitalWrite(ColourS2,HIGH);
	digitalWrite(ColourS3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(ColourOut, LOW);
  int rgb_value = map(PW, greenMin, greenMax, 255, 0); 

	return rgb_value;
}

// Function to read Blue Pulse Widths
int getBlueValue() {
	// Set sensor to read Blue only
	digitalWrite(ColourS2,LOW);
	digitalWrite(ColourS3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(ColourOut, LOW);
  int rgb_value = map(PW, blueMin, blueMax, 255, 0); 

	return rgb_value;
}
