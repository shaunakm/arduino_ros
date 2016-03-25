#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

//#include <sstream>
#include <ros.h>
//#include <Servo.h>
#include <VarSpeedServo.h>
#include <Arduino.h>
#include <std_msgs/UInt16.h>

using namespace std;

ros::NodeHandle nh;

//Servo servo;
VarSpeedServo servo;

void servo_cb(const std_msgs::UInt16& cmd_msgs)
{
	//std::cout<<"Angle of the servo is: "<<cmd_msgs.data;
	//ROS_INFO("Angle is");
	printf("angle is %d\n",cmd_msgs.data);
	servo.write(cmd_msgs.data);
	digitalWrite(13,HIGH-digitalRead(13));
}

ros::Subscriber<std_msgs::UInt16>sub("servo",servo_cb);

void setup()
{
	nh.initNode();
	nh.subscribe(sub);
	
	pinMode(13,OUTPUT);

	servo.attach(9);
}

void loop()
{
	nh.spinOnce();
	delay(10);
}