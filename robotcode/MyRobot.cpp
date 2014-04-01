#include "WPILib.h"
#include <stdio.h>
#include <iostream>
#define speed .15
#define speed_regulator .15
#define speed_regulator2 -.15

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	Joystick motorstick;
	Jaguar jag;//encoder jag/ arm
	Compressor comp; //compressor
	Encoder encoder;
	Solenoid shiftsol;  //shift solenoid one;
	Solenoid shiftsol2;
	Solenoid armsol1;	//lower arm solenoid 
	Solenoid armsol2;	//upper arm solenoid
	Solenoid upperarmsol1;
	Solenoid upperarmsol2;
	//Relay triggerrelay;
	Solenoid  triggersol;
	Jaguar roller1;
	Jaguar roller2;
	Jaguar belt;
	
public:
	RobotDemo():
		myRobot(1, 2),	// these must be initialized in the same order
		stick(1),		// as they are declared above.
		motorstick(2),
		jag(3),
		comp(3,1),
		encoder(1,2, false),
		shiftsol(1),
		shiftsol2(2),
		armsol1(4),
		armsol2(5),
		upperarmsol1(6),
		upperarmsol2(7),
		//triggerrelay(),
		triggersol(8),
		roller1(4),
		roller2(5),
		belt(6)
		
		
	{
		
		myRobot.SetInvertedMotor(myRobot.kFrontRightMotor, false);
		myRobot.SetInvertedMotor(myRobot.kFrontLeftMotor, true);
		myRobot.SetExpiration(0.1);
		encoder.Start();
		
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
		jag.Set(-.25);	
		Wait(2.0);										
		jag.Set(0);
		armsol2.Set(true);
		armsol1.Set(false);
		Wait(.25);
		belt.Set(.3);
		triggersol.Set(true);
		roller1.Set(0);
		roller2.Set(0);
		Wait(1);
		triggersol.Set(false);
	//	myRobot.Drive(-.5, 0);
		Wait(1);
		myRobot.Drive(0.0, 0);
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl()
	{
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl())
		{
			//#define e encoder.GetRaw();
			myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time
			
			jag.Set(0);
			belt.Set(1.0);
			
			roller1.Set(1);
			roller2.Set(1);
			triggersol.Set(false);
			comp.Start();
				
			if(stick.GetRawButton(7) == true){
							shiftsol.Set(true);
							shiftsol2.Set(false);
						}
						
			if (stick.GetRawButton(8) == true)
						 {
				shiftsol.Set(false);
				shiftsol2.Set(true);
						 }				 
				if(motorstick.GetRawButton(5) == true){
					armsol1.Set(false);
					armsol2.Set(true);
					upperarmsol2.Set(false);
					upperarmsol1.Set(true);
				}
				if(motorstick.GetRawButton(6) == true){
					armsol1.Set(true);
					armsol2.Set(false);
					upperarmsol2.Set(true);
					upperarmsol1.Set(false);
				}
			
				if(motorstick.GetRawButton(9) == true){
					armsol1.Set(true);
					armsol2.Set(false);
				}
				if(motorstick.GetRawButton(10) == true){
					armsol1.Set(false);
					armsol2.Set(true);
				}
				if(motorstick.GetRawButton(11) == true){
					upperarmsol2.Set(true);
					upperarmsol1.Set(false);
				}
				if(motorstick.GetRawButton(12) == true){
					upperarmsol2.Set(false);
					upperarmsol1.Set(true);
				}
				if(motorstick.GetY() >.05 or motorstick.GetY() <-.05
						or motorstick.GetY() <.25 or motorstick.GetY() > -.25){
						jag.Set(motorstick.GetY());
								}
				
				if(motorstick.GetRawButton(1) == true){
					belt.Set(.2);
					
					roller1.Set(0);
					roller2.Set(0);
					armsol1.Set(true);
					armsol2.Set(false);
					upperarmsol2.Set(true);
					upperarmsol1.Set(false);
					
					triggersol.Set(true);
					//roller1.Set(-1);
					//roller2.Set(-1);
				}
				if(motorstick.GetRawButton(2) == true) {
					triggersol.Set(true);
					belt.Set(.25);
								}
				if(motorstick.GetRawButton(3) == true){
					belt.Set(0);
					roller1.Set(-1);
					roller2.Set(-1);
				}
			
				if(motorstick.GetRawButton(7) == true)
				{
					encoder.Reset();
				}
				if (motorstick.GetRawButton(8) == true)
								{			
												
					while (encoder.GetRaw()  <= 100)
								{
							jag.Set(.2);		
								}
												
					while (encoder.GetRaw() > 300)
								{
					jag.Set(-.2);
								}
										
								}
				
				//relay reference below
				/*if(stick.GetRawButton(5) == true){
									relay.Set(Relay::kForward);
										
										}
							if(stick.GetRawButton(6) == true){
									relay.Set(Relay::kReverse);
										}
							if(stick.GetRawButton(7) == true){
									relay.Set(Relay::kOff);
										} */
				//encoder.GetRaw();
		
	
	/*while (encoder.GetRaw() != 0)
			{
		std::cout << encoder.GetRaw();
		
			}*/
	}
		
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
	}
};

START_ROBOT_CLASS(RobotDemo);

