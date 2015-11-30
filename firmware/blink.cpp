#include <ros.h>
#include <std_msgs/String.h>
#include <Arduino.h>

ros::NodeHandle nh;

//std_msgs::String str_msgs;

const int led_pin = 13;
String stringOn, stringOff;

void chatter_cb(const std_msgs::String& msg)
{
	//digitalWrite(led_pin, HIGH-digitalRead(led_pin));
	if(String(msg.data) == stringOn)
		digitalWrite(led_pin,HIGH);
	if(String(msg.data) == stringOff)
		digitalWrite(led_pin,LOW);
}

ros::Subscriber<std_msgs::String>sub("chatter",&chatter_cb);

void setup()
{
	stringOn = String("On");
	stringOff = String("Off");
	pinMode(led_pin,OUTPUT);
	nh.initNode();
	nh.subscribe(sub);
}

void loop()
{
	nh.spinOnce();
	delay(10);
}