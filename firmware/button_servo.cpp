#include <ros.h>
#include <std_msgs/Bool.h>
#include <Arduino.h>
#include <Servo.h>

ros::NodeHandle nh;

Servo servo;

std_msgs::Bool pushed_msg;
ros::Publisher pub_button("pushed",&pushed_msg);

const int button_pin = 7;
const int led_pin = 13;
const int servo_pin = 9;
int angle = 0;

boolean last_reading;
long last_debounce_time = 0;
long debounce_delay = 50;
boolean published = true;

void setup()
{
	nh.initNode();
	nh.advertise(pub_button);

	pinMode(led_pin,OUTPUT);
	pinMode(button_pin,INPUT);
	servo.attach(servo_pin);

	digitalWrite(button_pin,HIGH);

	last_reading = !digitalRead(button_pin);
}

void loop()
{
	int i;
	boolean reading = !digitalRead(button_pin);

	if(last_reading != reading)
	{
		last_debounce_time = millis();
		published = false;
	}

	if(!published && ((millis() - last_debounce_time) > debounce_delay))
	{
		digitalWrite(led_pin,!reading);
		pushed_msg.data = !reading;
		pub_button.publish(&pushed_msg);
		//servo.write(180);
		published = true;
	}

	if(!reading)
		for(angle;angle<180;angle++)
			servo.write(angle);
	else
		for(angle;angle>0;angle--)
			servo.write(angle);

	last_reading = reading;

	nh.spinOnce();

	delay(10);
}