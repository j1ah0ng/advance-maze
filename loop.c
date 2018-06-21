#pragma config(	Sensor,	port8,	,	sensorVexIQ_Gyro)
#pragma config(	Motor,	motor1,	leftMotor,	tmotorVexIQ,	openLoop,			driveLeft,	encoder)
#pragma config(	Motor,	motor6,	rightMotor,	tmotorVexIQ,	openLoop,	reversed,	driveRight,	encoder)
#pragma config(	Sensor,	port7,	,	sensorVexIQ_Distance)

#define GYRO	port8
#define SONAR	port7

//float goal;																								//Declare a float as a distance sensor offset.
float straightSpeed = 50;																		//Declare a float as the straight-line speed.
float turnSpeed = 15;																				//Declare a float as the turning speed.
float goalHeading;																					//Declare a float as the goal heading.

static void forwardsUntil(float goal) {																					//This task uses the gyro to maintain straight-ahead movement
	goalHeading = getGyroHeadingFloat(GYRO);																//Set the current heading.
	setMotorSpeed(leftMotor,	straightSpeed);																//Begin forwards movement.
	setMotorSpeed(rightMotor,	straightSpeed);

	repeatUntil(getDistanceValue(SONAR) == goal) {													//Begin feedback loop.
		if(abs(getGyroHeadingFloat(GYRO)-goalHeading) > 2) {									//If the heading becomes offset by more than 2deg,
			repeatUntil(abs(getGyroHeadingFloat(GYRO)-goalHeading) < 1) {
				if(goalHeading > getGyroHeadingFloat(GYRO)) {											//apply more power to the right motor if the offset is towards the left
					setMotorSpeed(leftMotor,	straightSpeed-5);
					setMotorSpeed(rightMotor,	straightSpeed+5);
				}
				else {																														//and apply more power to the left motor if the offset is towards the right.
					setMotorSpeed(leftMotor,	straightSpeed+5);
					setMotorSpeed(rightMotor,	straightSpeed-5);
				}
			}
		}
	}

	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
}

static void turnHeading(float goalHeading) {
	bool turnRight;
	if(goalHeading > getGyroHeadingFloat(GYRO)) {														//If the goal heading is to the left of the current heading,
		turnRight = false;																										//don't turn right.

		setMotorSpeed(leftMotor, turnSpeed * (-1));
		setMotorSpeed(rightMotor, turnSpeed);																				//Until the heading is within 1deg of the goal,
		repeatUntil(abs(goalHeading-getGyroHeadingFloat(GYRO)) < 1)	{}				//turn left.


	}
	else {																																	//If not,
		turnRight = true;																											//turn right.

		setMotorSpeed(leftMotor, turnSpeed);
		setMotorSpeed(rightMotor, turnSpeed * (-1));													//Until the heading is within 1deg of the goal,
		repeatUntil(abs(goalHeading-getGyroHeadingFloat(GYRO)) < 1)	{}				//turn left.

	}
}

task main() {
	resetGyro(GYRO);

	forwardsUntil(100);
	turnHeading(90);

	forwardsUntil(150);
	turnHeading(180);

	forwardsUntil(100);
	turnHeading(90);

	forwardsUntil(100);
	turnHeading(315);

	forwardsUntil(50);
	turnHeading(0);
}
