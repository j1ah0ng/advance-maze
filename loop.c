#pragma config(Sensor,	port8,	,	sensorVexIQ_Gyro)
#pragma config(Motor,	motor1,	leftMotor,	tmotorVexIQ,	openLoop,			driveLeft,	encoder)
#pragma config(Motor,	motor6,	rightMotor,	tmotorVexIQ,	openLoop,	reversed,	driveRight,	encoder)
#pragma config(Sensor,	port7,	,	sensorVexIQ_Distance)

#define GYRO	port8
#define SONAR	port7

//float goal;
float straightSpeed = 50;
float turnSpeed = 15;
float goalHeading;

static void forwardsUntil(float goal) {
    goalHeading = getGyroHeadingFloat(GYRO);
    setMotorSpeed(leftMotor,	straightSpeed);
    setMotorSpeed(rightMotor,	straightSpeed);

    repeatUntil(getDistanceValue(SONAR) == goal) {
        if(abs(getGyroHeadingFloat(GYRO)-goalHeading) > 2) {
            repeatUntil(abs(getGyroHeadingFloat(GYRO)-goalHeading) < 1) {
                if(goalHeading > getGyroHeadingFloat(GYRO)) {
                    setMotorSpeed(leftMotor,	straightSpeed-5);
                    setMotorSpeed(rightMotor,	straightSpeed+5);
                }
                else {
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
    if(goalHeading > getGyroHeadingFloat(GYRO)) {
        turnRight = false;

        setMotorSpeed(leftMotor, turnSpeed * (-1));
        setMotorSpeed(rightMotor, turnSpeed);
        repeatUntil(abs(goalHeading-getGyroHeadingFloat(GYRO)) < 1)	{}


    }
    else {
        turnRight = true;

        setMotorSpeed(leftMotor, turnSpeed);
        setMotorSpeed(rightMotor, turnSpeed * (-1));
        repeatUntil(abs(goalHeading-getGyroHeadingFloat(GYRO)) < 1)	{}

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
