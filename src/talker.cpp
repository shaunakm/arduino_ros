#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

using namespace std;

int main(int argc,char **argv)
{
	ros::init(argc,argv,"talker");

	ros::NodeHandle n;

	ros::Publisher msg_pub = n.advertise<std_msgs::String>("chatter",1000);

	ros::Rate loop_rate(10);
	int count = 0;

	while(ros::ok())
	{
		std_msgs::String msg;
		cout<<"Enter On/Off: ";
		cin>>msg.data;

		ROS_INFO("%s",msg.data.c_str());

		msg_pub.publish(msg);
		loop_rate.sleep();
		ros::spinOnce();
		++count;
	}

	return 0;
}