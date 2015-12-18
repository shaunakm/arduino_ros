#include <ros.h>
#include <Arduino.h>
#include <Servo.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle nh;

// Arduino pins for each joint servo.
const int led_pin = 13;
const int base_servo_pin = 3;
const int shoulder_servo_pin1 = 5;
const int shoulder_servo_pin2 = 6;
const int elbow_servo_pin = 9;
const int wrist_servo_pin = 10;
const int gripper_servo_pin = 11;
const int servo_pin1 = 9;
const int servo_pin2 = 10;

// Angle variables for each joint.
int base_angle = 90;
int shoulder_angle = 90;
int elbow_angle = 90;
int wrist_angle = 90;
int gripper_angle = 0;

// Servo objects for each servo.
Servo base_servo, shoulder_servo1, shoulder_servo2, elbow_servo, wrist_servo, gripper_servo;

// Callback function subscribing the joy_node which senses the changes in xbox controller and invokes he function.
void xbox_cb(const sensor_msgs::Joy& xbox_data)
{
	// Controlling base servo which is 360 degree servo.
	if(xbox_data.buttons[5] == 1)
	{
		if(base_angle <= 360)
			base_angle += 2;
		base_servo.write(base_angle);
	}
	if(xbox_data.buttons[6] == 1)
	{
		if(base_angle >= 2)
			base_angle -= 2;
		base_servo.write(base_angle);
	}

	// Code to control shoulder servos.
	if(xbox_data.axes[0] == 1)
	{
		if(shoulder_angle <=180)
			shoulder_angle += 2;
		shoulder_servo1.write(shoulder_angle);
		shoulder_servo2.write(shoulder_angle);
	}
	if(xbox_data.axes[0] == -1)
	{
		if(shoulder_angle >= 0)
			shoulder_angle -= 2;
		shoulder_servo1.write(shoulder_angle);
		shoulder_servo2.write(shoulder_angle);
	}

	// Code to control the elbow servo.
	if(xbox_data.axes[1] == 1)
	{
		if(elbow_angle <= 180)
			elbow_angle += 2;
		elbow_servo.write(elbow_angle);
	}
	if(xbox_data.axes[1] == -1)
	{
		if(elbow_angle >= 0)
			elbow_angle -= 2;
		elbow_servo.write(elbow_angle);
	}

	// Code to control wrist servo.
	if(xbox_data.axes[2] == 1)
	{
		if(wrist_angle <= 180)
			wrist_angle += 2;
		wrist_servo.write(wrist_angle);
	}
	if(xbox_data.axes[2] == -1)
	{
		if(wrist_angle >=0)
			wrist_angle -=2;
		wrist_servo.write(wrist_angle);
	}

	// Code to control the gripper.
	if(xbox_data.axes[3] == 1)
	{
		if(gripper_angle <= 180)
			gripper_angle += 2;
		gripper_servo.write(gripper_angle);
	}
	if(xbox_data.axes[3] == -1)
	{
		if(gripper_angle >= 0)
			gripper_angle -= 2;
		gripper_servo.write(gripper_angle);
	}

	digitalWrite(led_pin,HIGH-digitalRead(led_pin));
}

// Initializing subscriber named 'sub' for 'joy' node.
ros::Subscriber<sensor_msgs::Joy>sub("joy",&xbox_cb);

void setup()
{

	// Initialize the ROS node.
	nh.initNode();
	nh.subscribe(sub);

	// Setup the I/O pins.
	pinMode(led_pin, OUTPUT);
	base_servo.attach(base_servo_pin);
	shoulder_servo1.attach(shoulder_servo_pin1);
	shoulder_servo2.attach(shoulder_servo_pin2);
	elbow_servo.attach(elbow_servo_pin);
	wrist_servo.attach(wrist_servo_pin);
	gripper_servo.attach(gripper_servo_pin);
}

void loop()
{
	nh.spinOnce();
	delay(10);
}