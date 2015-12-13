#include <ros.h>
#include <Arduino.h>
#include <Servo.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle nh;

const int led_pin = 13;
const int servo_pin1 = 9;
const int servo_pin2 = 10;
int angle1 = 60;
int angle2 = 00;
int axis;

Servo servo1, servo2;

void xbox_cb(const sensor_msgs::Joy& xbox_data)
{
	//axis = xbox_data.axes[0];
	if(xbox_data.axes[0] == 1)
	{
		if(angle1 >= 0 && angle1 <=180)
			angle1 += 4;
		servo1.write(angle1);
		servo2.write(angle1);
		//digitalWrite(led_pin, HIGH);
	}
	if(xbox_data.axes[0] == -1)
	{
		if(angle1 >= 0 && angle1 <=180)
			angle1 -= 4;
		servo1.write(angle1);
		servo2.write(angle2);
		//digitalWrite(led_pin, LOW);
	}
	/*if(xbox_data.axes[1] == 1)
	{
		if(angle2 >=0 && angle2 <= 180)
			angle2 += 5;
		servo2.write(angle2);
	}
	if(xbox_data.axes[1] == -1)
	{
		if(angle2 >=0 && angle2 <= 180)
			angle2 -= 5;
		servo2.write(angle2);
	}*/
	digitalWrite(led_pin,HIGH-digitalRead(led_pin));

	//else
	//digitalWrite(led_pin,HIGH-digitalRead(led_pin));
}

ros::Subscriber<sensor_msgs::Joy>sub("joy",&xbox_cb);

void setup()
{
	nh.initNode();
	nh.subscribe(sub);

	pinMode(led_pin, OUTPUT);
	servo1.attach(servo_pin1);
	servo2.attach(servo_pin2);

	servo1.write(angle1);
	servo2.write(angle1);
}

void loop()
{
	nh.spinOnce();
	delay(10);
}