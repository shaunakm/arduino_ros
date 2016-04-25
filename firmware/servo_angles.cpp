// Node which subscribes to the /angle topic and writes the angle values on servo angle.
#include <ros.h>
#include <Arduino.h>
#include <arduino_ros/data.h>
#include <std_msgs/Bool.h>
#include <Servo.h>

ros::NodeHandle nh;

std_msgs::Bool done;
//ros::Publisher status("done_bit",&done);

// Arduino pins for each joint servo.
const int led_pin = 13;
const int base_servo_pin = 3;
const int shoulder_servo_pin1 = 5;
const int shoulder_servo_pin2 = 6;
const int elbow_servo_pin = 9;
const int wrist_servo_pin = 10;
const int gripper_servo_pin = 11;

// Angle variables for each joint.
int base_angle = 90;
int shoulder_angle = 100;
int elbow_angle = 90;
int wrist_angle = 30;
int gripper_angle = 20;
float current_shoulder;
float current_elbow;
bool flag = false;

// Servos objects for each servo.
Servo base_servo, shoulder_servo1, shoulder_servo2, elbow_servo, wrist_servo, gripper_servo;

// Callback function for inverse kinematics.
void kinematic_angles(const arduino_ros::data& angles_data)
{
	//flag = false;
	//status.publish(&done);

	if(angles_data.angles[0] >= 0 && angles_data.angles[1] >= 0 && angles_data.angles[2] >= 0)
	{
		
		base_servo.write(angles_data.angles[0]);
		shoulder_servo1.write(angles_data.angles[1]);
		shoulder_servo2.write(angles_data.angles[1]);
		elbow_servo.write(angles_data.angles[2]);
		//gripper_servo.write(angles_data.angles[3]);
		gripper_servo.write(60);
		nh.spinOnce();
		Serial.println("Hello there");
	}
   	digitalWrite(led_pin, HIGH-digitalRead(led_pin));

   	flag = true;
   	delay(100);
   	//status.publish(&done);
}

ros::Subscriber<arduino_ros::data>sub("angles",&kinematic_angles);

void setup()
{
	nh.initNode();
	//nh.advertise(status);
	nh.subscribe(sub);

	// Setup the I/O pins.
	pinMode(led_pin, OUTPUT);
	base_servo.attach(base_servo_pin);
	shoulder_servo1.attach(shoulder_servo_pin1);
	shoulder_servo2.attach(shoulder_servo_pin2);
	elbow_servo.attach(elbow_servo_pin);
	wrist_servo.attach(wrist_servo_pin);
	gripper_servo.attach(gripper_servo_pin);

	current_shoulder = 0;
	current_elbow = 0;
	base_servo.write(base_angle);
	shoulder_servo1.write(shoulder_angle);
	elbow_servo.write(elbow_angle);
	wrist_servo.write(wrist_angle);
	gripper_servo.write(gripper_angle);

}

void loop()
{
	//done.data = true;
	//done.data = flag;
   	//status.publish(&done);
	nh.spinOnce();
	delay(10);

	flag = false;
}