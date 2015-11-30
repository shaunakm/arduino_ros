#include "ros/ros.h"
#include "std_msgs/UInt16.h"

using namespace std;
std_msgs::UInt16 int_angle;

int main(int argc,char **argv)
{
	ros::init(argc,argv,"servo_pub");
	ros::NodeHandle n;

	ros::Publisher angle_pub = n.advertise<std_msgs::UInt16>("servo_angle",1000);
	ros::Rate loop_rate(10);

	while(ros::ok())
	{
		cout<<"Enter the angle(0-180): ";
		cin>>int_angle.data;
		angle_pub.publish(int_angle);
		loop_rate.sleep();
		ros::spinOnce();
	}

	return 0;
}