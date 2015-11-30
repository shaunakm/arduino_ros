#include <ros.h>
#include <std_msgs/UInt16.h>
#include <Servo.h>
#include <Arduino.h>

ros::NodeHandle nh;

Servo servo;

const int servo_pin = 9;
const int led_pin = 13;

void angle_cb(const std_msgs::UInt16& angle)
{
	if(int(angle.data) > 180)
		digitalWrite(led_pin,HIGH-digitalRead(led_pin));
	else
		servo.write(int(angle.data));
}

ros::Subscriber<std_msgs::UInt16>sub("servo_angle",angle_cb);

void setup()
{
	nh.initNode();
	nh.subscribe(sub);

	pinMode(led_pin,OUTPUT);
	servo.attach(servo_pin);
}

void loop()
{
	nh.spinOnce();
	delay(10);
}