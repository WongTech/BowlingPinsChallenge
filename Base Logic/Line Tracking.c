#pragma config(Sensor, S1, lightSensor, sensorLightActive)

/*--------------------------------------------------------------------------------------------------------*\
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port B                  motorB              NXT                 Right motor                         *|
|*    Port C                  motorC              NXT                 Left motor                          *|
|*    Port 1                  lightSensor         Light Sensor        Back mounted                        *|
\*---------------------------------------------------------------------------------------------------4246-*/

// Define the directions.
#define LEFT true
#define RIGHT (!LEFT)

// Define the colour ranges.
#define BLACK_END 37
#define GREEN_START BLACK_END
#define GREEN_END 50
#define WHITE_START GREEN_END

// Define the motor values.
#define HIGH 30
#define LOW 2

// The value of the light sensor on this tick.
int light;

// Return whether or not we are currently on black.
bool onBlack() {
	return (light < BLACK_END);
}

// Return whether or not we are currently on green.
bool onGreen() {
	return (light >= GREEN_START && light < GREEN_END);
}

// Return whether or not we are currently on white.
bool onWhite() {
	return (light >= WHITE_START);
}

void goLeft() {
	motor[motorB] = HIGH; // Set right motor to low.
	motor[motorC] = LOW; // Set left motor to high.
}

void goRight() {
	motor[motorB] = LOW; // Set right motor to low.
	motor[motorC] = HIGH; // Set left motor to high.
}

// Set the direction to turn.
void setDirection(bool newDir) {
	if (newDir == LEFT) {
		goLeft();
	} else {
		goRight();
	}
}

task main() {
	wait1Msec(50); // The program waits 50 milliseconds to initialize the light sensor.
	setDirection(RIGHT);
	while (true) {
		light = SensorValue[lightSensor];
		if (onBlack() || onGreen()) {
			setDirection(RIGHT);
		} else {
			setDirection(LEFT);
		}
	}
}
