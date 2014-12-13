#include "WPILib.h"

/**
 * This is the code to operate the demo Ping Pong Bot of Doom
 */
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // Robot Drive System
	Joystick stick;    // Joystick
	Jaguar shooter;   // The Jaguar that controls the wheel
	Jaguar indexer;  // The Jaguar that runs the indexer
public:
	RobotDemo():
		myRobot(1, 2),	// These must be initialized in the same order
		stick(1),	   // As they are declared above.
		shooter(3),   // We are using the Jaguaur labeled 3
		indexer(4)   // We are using the Jaguar labeled 4
	{
		myRobot.SetExpiration(0.1);
	}
	void Autonomous()
	{

	}

	void OperatorControl()
	{
		bool wheelEnabledBehavior = false;
		double wheelSpeed = 0.25;
		bool rightBumperPressed = false;
		bool joysticksPressed = false;
		bool reverseMode = false;
		bool slowMode = false;
		bool wasSlowButtonPressed = false;
		bool wasReverseButtonPressed = false;
		
		
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled()) 
		{
			//SLOW MODE LOGIC
						if (stick.GetRawButton(3))
						{
							if(!wasSlowButtonPressed){
								slowMode=!slowMode;
							}
							wasSlowButtonPressed = true;
						}
						else
							wasSlowButtonPressed = false;
						
						//REVERSE MODE LOGIC
						if (stick.GetRawButton(2))
						{
							if(!wasReverseButtonPressed){
								reverseMode=!reverseMode;
							}
							wasReverseButtonPressed = true;
						}
						else
							wasReverseButtonPressed = false;
						
			// tank drive input
			double leftStickSpeed, rightStickSpeed;
			if(!reverseMode)
			{
				leftStickSpeed = stick.GetRawAxis(2);
				rightStickSpeed = stick.GetRawAxis(4);
			}
			if (reverseMode)
			{
				leftStickSpeed = -stick.GetRawAxis(4);
				rightStickSpeed = -stick.GetRawAxis(2);
			}
			
			if (slowMode)
			{
				leftStickSpeed*=0.5;
				rightStickSpeed*=0.5;
			}
			myRobot.TankDrive(leftStickSpeed, rightStickSpeed); // Tank Drive
			
			// Toggle logic for right bumper
			if (stick.GetRawButton(6)== 1)
			{
				if (!rightBumperPressed) 
				{
					wheelEnabledBehavior = !wheelEnabledBehavior;
					wheelSpeed = 0.25;
				    printf("Toggled Wheel\n");
				}
				rightBumperPressed = true;
			} 
			else 
			{
				rightBumperPressed = false;
			}
			
			// Toggle logic for twin joystick safety presses
			if (stick.GetRawButton(11)&& stick.GetRawButton(12))
			{
				if(!joysticksPressed)
				{
					wheelSpeed = wheelSpeed +0.25;
					if (wheelSpeed > 1.0)
					{
						wheelSpeed = 0.25;
					}
					printf ("current speed: %g\n", wheelSpeed);
				}
				joysticksPressed = true;
			} 
			else 
			{
				joysticksPressed = false;
			}
			
			if (wheelEnabledBehavior)
			{
				shooter.SetSpeed(wheelSpeed);
			}
			else
			{
				shooter.SetSpeed(0.0);
			}
			
			if (stick.GetRawButton(8) == 1)
			{
				indexer.SetSpeed(1.0);
				printf("Fully Automatic Fire");
			}
//			If the right trigger is pressed shoot at a constant speed 
//			and print "Fully Automatic Fire" on the console 
			Wait(0.005);                                               // Wait for a motor update time
		}
	}
};
START_ROBOT_CLASS(RobotDemo);


