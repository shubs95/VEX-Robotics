#pragma config(Sensor, in1,    armPot,         sensorPotentiometer)
#pragma config(Sensor, in2,    autonPot,       sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11, leftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port1,           rightArm,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           frontRightDrive, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           rightIntake,   tmotorVex393, openLoop)
#pragma config(Motor,  port4,           leftConveyor,  tmotorVex393, openLoop)
#pragma config(Motor,  port5,           backRightDrive, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           backLeftDrive, tmotorVex393, openLoop)
#pragma config(Motor,  port7,           rightConveyor, tmotorVex393, openLoop)
#pragma config(Motor,  port8,           leftIntake,    tmotorVex393, openLoop)
#pragma config(Motor,  port9,           frontLeftDrive, tmotorVex393, openLoop)
#pragma config(Motor,  port10,          leftArm,       tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#define centerButton 			2
#define rightButton				4
int autonRoutine = 0;
int spatulaPot = 0;
/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

/*Miscellanaeous Functions*/
void clearLines()
{
  clearLCDLine(0);                      // Clear line 1 (0) of the LCD
  clearLCDLine(1);                      // Clear line 2 (1) of the LCD
}

void clearEncoders()
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
}

void initializeGyro()
{
	SensorType[in3] = sensorNone;
	wait1Msec(1000);
	SensorType[in3] = sensorGyro;
	wait1Msec(2000);
}

/*Autonomous Functions*/
void GyroTurnLeft(int degrees, int speed)
{
	SensorValue[gyro] = 0;
	while(SensorValue[gyro] < degrees)
	{
		motor[frontRightDrive] = speed;
		motor[backRightDrive] =  speed;

		motor[frontLeftDrive] = -speed;
		motor[backLeftDrive] =  -speed;
	}
		motor[frontRightDrive] = 0;
		motor[backRightDrive] =  0;

		motor[frontLeftDrive] = 0;
		motor[backLeftDrive] =  0;
}

void GyroTurnRight(int degrees, int speed)
{
	SensorValue[gyro] = 0;
	while(SensorValue[gyro] > degrees)
	{
		motor[frontRightDrive] = -speed;
		motor[backRightDrive] =  -speed;

		motor[frontLeftDrive] = speed;
		motor[backLeftDrive] =  speed;
	}
		motor[frontRightDrive] = 0;
		motor[backRightDrive] =  0;

		motor[frontLeftDrive] = 0;
		motor[backLeftDrive] =  0;
}

void forwardEncoder(int counts, int speed, int timeOutInSecs)
{
	clearEncoders();

	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while((SensorValue[leftEncoder] < counts) || (SensorValue[rightEncoder] < counts))
	{
		currTime = time1[T1];
		if(currTime > timeOut) 
			break;
		motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
		motor[frontLeftDrive] = speed;
		motor[backLeftDrive] = speed;
	}

	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;
	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] = 0;
}

void backwardEncoder(int counts, int speed, int timeOutInSecs)
{
	clearEncoders();

	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while((SensorValue[leftEncoder] > counts) || (SensorValue[rightEncoder] > counts))
	{
		currTime = time1[T1];
		if(currTime > timeOut) 
			break;
	    motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
		motor[frontLeftDrive] = speed;
		motor[backLeftDrive] = speed;
	}

	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;
	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] = 0;
}

void constantForwardEncoder(int counts, int speed, int armHoldSpeed, int timeOutInSecs)
{
	clearEncoders();

	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while((SensorValue[leftEncoder] < counts) || (SensorValue[rightEncoder] < counts))
	{
		currTime = time1[T1];
		if(currTime > timeOut) 
			break;
		motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
		motor[frontLeftDrive] = speed;
		motor[backLeftDrive] = speed;

		motor[rightArm] = armHoldSpeed;
		motor[leftArm] = armHoldSpeed;
	}

	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;
	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] = 0;

	motor[rightArm] = 0;
	motor[leftArm] = 0;
}

void constantBackwardEncoder(int counts, int speed, int armHoldSpeed, int timeOutInSecs)
{
	clearEncoders();

	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while((SensorValue[leftEncoder] > counts) || (SensorValue[rightEncoder] > counts))
	{
		currTime = time1[T1];
		if(currTime > timeOut) 
			break;
		motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
		motor[frontLeftDrive] = speed;
		motor[backLeftDrive] = speed;
		
		motor[rightArm] = armHoldSpeed;
		motor[leftArm] = armHoldSpeed;
	}

	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;
	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] = 0;

	motor[rightArm] = 0;
	motor[leftArm] = 0;
}

void onlyRightEncoder(int counts, int speed, int timeOutInSecs)
{
	clearEncoders();

	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];
	while(SensorValue[rightEncoder] < counts)
	{
		currTime = time1[T1];
		if(currTime > timeOut) 
			break;
		motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
	}
	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;
}

void backwardOnlyRightEncoder(int counts, int speed, int timeOutInSecs)
{
	clearEncoders();
	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while(SensorValue[rightEncoder] > counts)
	{
		currTime = time1[T1];
		if(currTime > timeOut)
			break;
		motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
	}
	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;
}

void moveArmUp(int target, int speed, int timeOutInSecs)
{
	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while (SensorValue[armPot] > target)
	{
		currTime = time1[T1];
		if(currTime > timeOut)
			break;
		motor[rightArm] = speed;
		motor[leftArm] = speed;
	}
	motor[rightArm] = 15;
	motor[leftArm] = 15;
}

void moveArmDown(int target, int speed, int timeOutInSecs)
{
	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while (SensorValue(armPot) < target)
	{
		currTime = time1[T1];
		if(currTime > timeOut)
			break;
		motor[rightArm] = speed;
		motor[leftArm] = speed;
	}
	motor[rightArm] = 0;
	motor[leftArm] = 0;
}

void forwardEncoderAndArm(int counts, int speed, int armSpeed, int timeOutInSecs)
{
	clearEncoders();

	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while(SensorValue[leftEncoder] < counts || SensorValue[rightEncoder] < counts)
	{
	  currTime = time1[T1];
		if(currTime > timeOut)
			break;

		motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
		motor[frontLeftDrive] = speed;
		motor[backLeftDrive] = speed;

		motor[rightArm] = armSpeed;
		motor[leftArm] = armSpeed;
	}
	
	motor[frontRightDrive] = 0;
	motor[backRightDrive] = 0;
	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] = 0;

	if (armSpeed > 0)
	{
		motor[rightArm] = 15;
		motor[leftArm] = 15;
	}

	else if (armSpeed < 0)
	{
		motor[rightArm] = 0;
		motor[leftArm] = 0;
	}
}

void backwardEncoderAndArm(int counts, int speed, int armSpeed, int timeOutInSecs)
{
	clearEncoders();

	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while(SensorValue[leftEncoder] > counts || SensorValue[rightEncoder] > counts)
	{
		currTime = time1[T1];
		if(currTime > timeOut) 
			break;

		motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
		motor[frontLeftDrive] = speed;
		motor[backLeftDrive] = speed;

		motor[rightArm] = armSpeed;
		motor[leftArm] = armSpeed;
	}
    motor[frontRightDrive] = 0;
	motor[backRightDrive] =  0;
	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] =  0;

	if (armSpeed > 0)
	{
		motor[rightArm] = 15;
		motor[leftArm] = 15;
	}

	else if (armSpeed < 0)
	{
		motor[rightArm] = 0;
		motor[leftArm] = 0;
	}
}

void driveForwardWithIntake(int counts, int speed, int timeOutInSecs) {
	clearEncoders();

	ClearTimer(T1);
	int timeOut = timeOutInSecs;
	int currTime = time1[T1];

	while(SensorValue[leftEncoder] < counts || SensorValue[rightEncoder] < counts)
	{
		currTime = time1[T1];
		if(currTime > timeOut)
			break;

		motor[frontRightDrive] = speed;
		motor[backRightDrive] = speed;
		motor[frontLeftDrive] = speed;
		motor[backLeftDrive] = speed;

		motor[leftIntake] = -127;
		motor[rightIntake] = 127;
		motor[leftConveyor] = 127;
		motor[rightConveyor] = -127;
	}
	motor[frontRightDrive] = 0;
	motor[backRightDrive] =  0;
	motor[frontLeftDrive] = 0;
	motor[backLeftDrive] =  0;

	motor[leftIntake] = 0;
	motor[rightIntake] = 0;
	motor[leftConveyor] = 0;
	motor[rightConveyor] = 0;
}

void intakeRoller(int timeOut) {
	motor[leftIntake] = -127;
	motor[rightIntake] = 127;
	motor[leftConveyor] = 127;
	motor[rightConveyor] = -127;

	wait1Msec(timeOut);

	motor[leftIntake] = 0;
	motor[rightIntake] = 0;
	motor[leftConveyor] = 0;
	motor[rightConveyor] = 0;
}

void outtakeRoller(int timeOut) {
	motor[leftIntake] = 127;
	motor[rightIntake] = -127;
	motor[leftConveyor] = -127;
	motor[rightConveyor] = 127;

	wait1Msec(timeOut);

	motor[leftIntake] = 0;
	motor[rightIntake] = 0;
	motor[leftConveyor] = 0;
	motor[rightConveyor] = 0;
}

task LCD()//when left button is pressed, the Auton Pot value is displayed, when center button is pressed team name is displayed
{         //when right button is pressed, you can go through all of the different sensors on the robot
	short scroll;

	clearLines();
	scroll = 4;

	nLCDRefreshRate = 200;
	bLCDBacklight = true;                 // Turn on LCD Backlight

	displayLCDCenteredString(0, "1241X");
	while (true)
	{
		//Items to display and update on VEX LCD screen. Simulated one can be found under Robot / Debug Windows / VEX Remote Screen
		if (nLCDButtons == centerButton)
		{
			clearLines();
			while (nLCDButtons == 0 && scroll == 5)
			{
				displayLCDCenteredString(0, "1241X");
			}
		}
		else if (nLCDButtons == rightButton)
		{
			scroll = 0;

			while ((scroll == 0) || (scroll == 1) || (scroll == 2) || (scroll == 3) || (scroll == 4))
			{
				clearLines();
				if (scroll ==0)
				{
					//Drive Encoders
					displayLCDCenteredString(0,"Encoders");
					displayLCDPos(1, 0);
					displayNextLCDString("L:");
					displayLCDPos(1, 3);
					displayNextLCDNumber(SensorValue[leftEncoder], 5);
					displayLCDPos(1, 9);
					displayNextLCDString("R:");
					displayLCDPos(1, 11);
					displayNextLCDNumber(SensorValue[rightEncoder], 5);
					wait1Msec(200);
					if (nLCDButtons == rightButton)
					{
						clearLines();
						scroll++;
					}

					else if ((nLCDButtons == 2))
					{
						scroll = 5;
					}

					else if (nLCDButtons == 1)
					{
						scroll--;
					}
				}

				else if (scroll == 1)
				{
					//clearLines();
					//Gyro
					displayLCDCenteredString(0, "Gyro");
					displayLCDPos(1, 0);
					displayNextLCDString("Value: ");
					displayLCDPos(1, 8);
					displayNextLCDNumber(SensorValue[gyro], 5); //gyro
					wait1Msec(200);
					if (nLCDButtons == rightButton)
					{
						clearLines();
						scroll++;
					}
					else if ((nLCDButtons == 2))
					{
						scroll = 5;
					}

					else if (nLCDButtons == 1)
					{
						scroll--;
					}
				}

				else if (scroll== 2)
				{
					//clearLines();
					//Arm Pot
					displayLCDCenteredString(0, "Arm Pot");
					displayLCDPos(1, 0);
					displayNextLCDString("Value: ");
					displayLCDPos(1, 8);
					displayNextLCDNumber(SensorValue[armPot], 5);
					wait1Msec(200);

					if (nLCDButtons == rightButton)
					{
						clearLines();
						scroll++;
					}

					else if ((nLCDButtons == 2))
					{
						scroll = 5;
					}

					else if (nLCDButtons == 1)
					{
						scroll--;
					}
				}

				else if (scroll == 3)
				{
					displayLCDCenteredString(0, "Auton Pot");
					displayLCDPos(1, 0);
					displayNextLCDString("Auton: ");
					displayLCDPos(1, 8);

					if (SensorValue[autonPot] <= 500)
					{
						displayNextLCDString("PSC");
						autonRoutine = 1;
					}
					else if (SensorValue[autonPot] > 500 && SensorValue[autonPot] <= 1000)
					{
						displayNextLCDString("leftDefensive");
						autonRoutine = 2;
					}
					else if (SensorValue[autonPot] > 1000 && SensorValue[autonPot] <= 1500)
					{
						displayNextLCDString("rightDefensive");
						autonRoutine = 3;
					}
					else if (SensorValue[autonPot] > 1500 && SensorValue[autonPot] <= 2000)
					{
						displayNextLCDString("twoPyramidYellow");
						autonRoutine = 4;
					}
					else if (SensorValue[autonPot] > 2000 && SensorValue[autonPot] <= 2500)
					{
						displayNextLCDString("LeftpyramidYellow");
						autonRoutine = 5;
					}
					else
					{
						displayNextLCDString("RightpyramidYellow");
						autonRoutine = 6;
					}
					wait1Msec(200);

					if (nLCDButtons == rightButton)
					{
						clearLines();
						scroll++;
					}

					else if ((nLCDButtons == 2))
					{
						scroll = 5;
					}

					else if (nLCDButtons == 1)
					{
						scroll--;
					}
				}

				else if (scroll == 4)
				{
					displayLCDCenteredString(0, "Spatula Pot");
					displayLCDPos(1, 0);
					displayNextLCDString("Value: ");
					displayLCDPos(1, 8);
					displayNextLCDNumber(SensorValue[spatulaPot], 5);
					wait1Msec(200);

					if (nLCDButtons == rightButton)
					{
						clearLines();
						scroll++;
					}

					else if ((nLCDButtons == 2))
					{
						scroll = 5;
					}

					else if (nLCDButtons == 1)
					{
						scroll--;
					}
				}
			}// end while
		}//end of if
	}// end of while loop in task LCD
}// end of task LCD


task armControl()
{
	float rawArmSpeed;
	float scaledArmSpeed;
	while (true)
	{
		rawArmSpeed = vexRT[Ch2Xmtr2];
		rawArmSpeed /= 127;
		scaledArmSpeed = pow(rawArmSpeed, 3);
		scaledArmSpeed *= 127;

		if (abs(scaledArmSpeed) > 5)
		{
			motor[rightArm] = scaledArmSpeed;
			motor[leftArm] = scaledArmSpeed;
		}

		else if (SensorValue[armPot] < 2200) {
		  motor[leftArm] = 20;
		  motor[rightArm] = 20;
	    }

		else
		{
			motor[leftArm] = 0;
			motor[rightArm] = 0;
		}
	}
}

task driveControl()
{
	float rawLeftSpeed;
	float rawRightSpeed;
	float scaledRightSpeed;
	float scaledLeftSpeed;

	while (true)
	{
		rawLeftSpeed = vexRT[Ch3];
		rawRightSpeed = vexRT[Ch2];

		rawLeftSpeed /= 127;
		rawRightSpeed /= 127;

		scaledLeftSpeed = pow(rawLeftSpeed, 3);
		scaledRightSpeed = pow(rawRightSpeed,3);

		scaledLeftSpeed *= 127;
		scaledRightSpeed *= 127;

		if(vexRT[Btn6U] == 1 && vexRT[Btn6D] == 0)
		{
			scaledLeftSpeed /= 2;
			scaledRightSpeed /= 2;
		}

		else if(vexRT[Btn6U] == 0 && vexRT[Btn6D] == 1)
		{
			scaledLeftSpeed /= 4;
			scaledRightSpeed /= 4;
		}

		motor[backLeftDrive] = scaledLeftSpeed;
		motor[frontLeftDrive] = scaledLeftSpeed;
		motor[backRightDrive] = scaledRightSpeed;
		motor[frontRightDrive] = scaledRightSpeed;
	}
}

task intake()
{
	while (true)
	{
		if(vexRT[Btn6UXmtr2] && !vexRT[Btn6DXmtr2]) {
			motor[leftIntake] = 127;
			motor[rightIntake] = -127;
			motor[leftConveyor] = -127;
			motor[rightConveyor] = 127;
		}

		else if(!vexRT[Btn6UXmtr2] && vexRT[Btn6DXmtr2]) {
			motor[leftIntake] = -127;
			motor[rightIntake] = 127;
			motor[leftConveyor] = 127;
			motor[rightConveyor] = -127;
		}

		else {
			motor[leftIntake] = 0;
			motor[rightIntake] = 0;
			motor[leftConveyor] = 0;
			motor[rightConveyor] = 0;
		}
	}
}

void TenSackAuton() {
	intakeRoller(1000);
	wait1Msec(1000);
	motor[rightArm] = -50;
	motor[leftArm] = -50;
	driveForwardWithIntake(150, 127, 2000);
	//driveForwardWithIntake(250, 63, 2000);
	//driveForwardWithIntake(250, 60, 3000);
	wait1Msec(150);
	intakeRoller(700);
	//GyroTurnRight(-90, 70);
	//backwardEncoder(-50, -60, 2000);
	//wait1Msec(250);
	driveForwardWithIntake(25, 70, 1000);
	intakeRoller(1500);
	motor[rightArm] = 0;
	motor[leftArm] = 0;
	backwardEncoder(-9, -70, 1000);
	wait1Msec(150);
	GyroTurnRight(-55, 60);
	wait1Msec(150);
	driveForwardWithIntake(100, 127, 1500);
	intakeRoller(900);
	motor[leftIntake] = -127;
	motor[rightIntake] = 127;
	motor[leftConveyor] = 127;
	motor[rightConveyor] = -127;
	backwardEncoder(-30, -70, 1000);
	wait1Msec(150);
	onlyRightEncoder(230, 100, 1500);
	intakeRoller(500);
	wait1Msec(150);
	backwardOnlyRightEncoder(-200, -100, 1500);
	backwardEncoder(-10, -127, 1500);
	moveArmUp(1500, 127, 3000);
	constantForwardEncoder(100, 100, 30, 1500);
}

void pyramidAndYellowRightAuton() {
	//intakeRoller(1000);
	//wait1Msec(1000);
	//motor[rightArm] = -50;
	//motor[leftArm] = -50;
	//driveForwardWithIntake(135, 127, 2000);
	//wait1Msec(150);
	//intakeRoller(700);
	//driveForwardWithIntake(30, 70, 1000);
	//intakeRoller(950);
	//motor[rightArm] = 0;
	//motor[leftArm] = 0;
	//GyroTurnLeft(500, 70);
	//wait1Msec(150);
	//driveForwardWithIntake(175, 70, 2000);
	//wait1Msec(150);
	//backwardEncoderAndArm(-100, -80,127, 2000);
	//moveArmUp(1500, 127, 2000);
	//GyroTurnRight(-700, 60);
	//wait1Msec(150);
	//constantForwardEncoder(93, 70, 30, 2000);
	//outtakeRoller(950);
	//constantBackwardEncoder(-100, -70, 30, 2000);
	intakeRoller(1000);
	wait1Msec(100);
	motor[rightArm] = -50;
	motor[leftArm] = -50;
	driveForwardWithIntake(200, 127, 2000);
	driveForwardWithIntake(100, 63, 2000);
	intakeRoller(700);
	motor[rightArm] = 0;
	motor[leftArm] = 0;
	wait1Msec(50);
	backwardEncoder(-250, -127, 2000);
	wait1Msec(1000);
	motor[rightArm] = -50;
	motor[leftArm] = -50;
	driveForwardWithIntake(135, 127, 2000);
	wait1Msec(150);
	intakeRoller(700);
	driveForwardWithIntake(30, 70, 1000);
	wait1Msec(100);

	intakeRoller(950);

	motor[rightArm] = 0;
	motor[leftArm] = 0;
	driveForwardWithIntake(135, 70, 1000);
	GyroTurnRight(-80, 60);
	intakeRoller(700);
	//GyroTurnLeft(80, 60);
	backwardEncoder(-95, -127, 2000);
	moveArmUp(1400, 127, 2000);
	motor[rightArm] = 60;
	motor[leftArm] = 60;
	constantForwardEncoder(153, 100, 70, 2000);
	motor[rightArm] = 70;
	motor[leftArm] = 70;
	outtakeRoller(1300);
	wait1Msec(250);
	backwardEncoder(-150, -100, 2000);
}

void pre_auton()
{
	bStopTasksBetweenModes = true;
	SensorValue[leftEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	initializeGyro();
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	//intakeRoller(1000);
	//wait1Msec(1000);
	//motor[rightArm] = -50;
	//motor[leftArm] = -50;
	//driveForwardWithIntake(135, 127, 2000);
	//wait1Msec(150);
	//intakeRoller(700);
	//driveForwardWithIntake(30, 70, 1000);
	//intakeRoller(950);
	//motor[rightArm] = 0;
	//motor[leftArm] = 0;
	//GyroTurnLeft(470, 70);
	//wait1Msec(150);
	//driveForwardWithIntake(160, 70, 2000);
	//intakeRoller(250);
	//wait1Msec(150);
	//backwardEncoder(-115, -180, 2000);
	//wait1Msec(200);
	//GyroTurnRight(-700, 60);
	//wait1Msec(150);
	//driveForwardWithIntake(93, 70, 2000);
	//intakeRoller(1000);
	//backwardEncoder(-115, -80, 2000);
	//moveArmUp(1400, 127, 2000);
	//constantForwardEncoder(140, 70, 70, 2000);
	//motor[leftArm] = 70;
	//motor[rightArm] = 70;
	//outtakeRoller(1100);
	//constantBackwardEncoder(-100, -80, 70, 2000);
	//motor[leftArm] = 0;
	//motor[rightArm] = 0;
	pyramidAndYellowRightAuton();
}

task usercontrol()
{
 initializeGyro();
 StartTask(driveControl);
 StartTask(armControl);
 StartTask(intake);
 StartTask(LCD);
}
