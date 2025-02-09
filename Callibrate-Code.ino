// Define color sensor pins
#define ColourOut A0
#define ColourS0 A1
#define ColourS1 A2
#define ColourS3 A3
#define ColourS2 A4

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

long redSum = 0;
long greenSum = 0;
long blueSum = 0;

long redAvg;
long greenAvg;
long blueAvg;

unsigned long count;

void setup() {
	// Set S0 - S3 as outputs
	pinMode(ColourS0, OUTPUT);
	pinMode(ColourS1, OUTPUT);
	pinMode(ColourS2, OUTPUT);
	pinMode(ColourS3, OUTPUT);

	// Set Pulse Width scaling to 20%
	digitalWrite(ColourS0,HIGH);
	digitalWrite(ColourS1,LOW);

	// Set Sensor output as input
	pinMode(ColourOut, INPUT);

	// Setup Serial Monitor
	Serial.begin(9600);
}

void loop() {
  count += 1;

	// Read Red Pulse Width
	redPW = getRedPW();
  redSum += redPW;
  long redAvg = redSum / count;
	// Delay to stabilize sensor
	delay(200);


	// Read Green Pulse Width
	greenPW = getGreenPW();
  greenSum += greenPW;
  greenAvg = greenSum / count;
	// Delay to stabilize sensor
	delay(200);

	// Read Blue Pulse Width
	bluePW = getBluePW();
  blueSum += bluePW;
  blueAvg = blueSum / count;
	// Delay to stabilize sensor
	delay(200);

	// Print output to Serial Monitor
	Serial.print("Red Avg = ");
	Serial.print(redAvg);
	Serial.print(" - Green Avg = ");
	Serial.print(greenAvg);
	Serial.print(" - Blue Avg = ");
	Serial.println(blueAvg);
}


// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(ColourS2,LOW);
	digitalWrite(ColourS3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(ColourOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(ColourS2,HIGH);
	digitalWrite(ColourS3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(ColourOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(ColourS2,LOW);
	digitalWrite(ColourS3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(ColourOut, LOW);
	// Return the value
	return PW;
}
