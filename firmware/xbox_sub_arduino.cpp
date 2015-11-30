#include <ros.h>
#include <std_msgs/String.h>
#include <Arduino.h>
#include <Servo.h>

ros::NodeHandle nh;

const int led_pin = 13;
const int servo_pin = 9;
String stringOn, stringOff;

int last_value = 90;

Servo servo;

void msg_cb(const std_msgs::String& xbox_data)
{
	if(String(xbox_data.data) == stringOn)
	{
		int i;
		digitalWrite(led_pin,HIGH);
		for(i = last_value;i>0;i--)
			servo.write(i);
	}
    else if(String(xbox_data.data) == stringOff)
    {
    	int i;
		digitalWrite(led_pin,LOW);
		for(i = last_value;i<180;i++)
			servo.write(i);
	}
	else
		digitalWrite(led_pin,HIGH-digitalRead(led_pin));
}
	
ros::Subscriber<std_msgs::String>sub("controller_data",&msg_cb);

void setup()
{
	stringOn = String("rr");
	stringOff = String("rl");
	pinMode(led_pin,OUTPUT);
	servo.attach(servo_pin);

	nh.initNode();
	nh.subscribe(sub);	
}

void loop()
{
	nh.spinOnce();
	delay(10);
}