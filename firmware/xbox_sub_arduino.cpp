#include <ros.h>
#include <std_msgs/String.h>
#include <Arduino.h>
#include <Servo.h>

ros::NodeHandle nh;

const int led_pin = 13;
const int servo_pin = 9;
String stringOn, stringOff;

int angle = 90;

Servo servo;

void msg_cb(const std_msgs::String& xbox_data)
{

	if(String(xbox_data.data) == stringOn)
	{
		angle -= 5;
		digitalWrite(led_pin,HIGH);  // Right rotation
		if(angle>=0 && angle <=180)
			servo.write(angle);
	}
    else if(String(xbox_data.data) == stringOff)
    {
   		angle +=5;
		digitalWrite(led_pin,LOW);	// Left rotation
		if(angle>=0 && angle <=180)
			servo.write(angle);
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

	servo.write(90);

	nh.initNode();
	nh.subscribe(sub);	
}

void loop()
{
	nh.spinOnce();
	delay(10);
}