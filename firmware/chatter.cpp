// To run ir use following set of commands.
//1. $catkin_make arduino_ros_firmware_hello
//2. $catkin_make arduino_ros_firmware_hello-upload
//3. $rosrun rossrial_python serial_node.py /dev/ttyACM0
//4. $rostopic echo chatter

#include <ros.h>
#include <std_msgs/String.h>

#include <Arduino.h>

ros::NodeHandle nh;

std_msgs::String str_msgs;

ros::Publisher chatter("chatter",&str_msgs);

char hello[15] = "Shaunak rock!";

void setup()
{
	nh.initNode();
	nh.advertise(chatter);
}

void loop()
{
	str_msgs.data = hello;
	chatter.publish(&str_msgs);
	delay(1000);
	nh.spinOnce();
}