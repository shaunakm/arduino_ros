#include "ros/ros.h"
#include "arduino_ros/data.h"

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc,argv,"joint_angle");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<arduino_ros::data>("angles",100);
	ros::Rate loop_rate(10);

	while(ros::ok())
	{
		arduino_ros::data joint_angles;
		cout<<"Enter the angles of the joint: ";
		cin>>joint_angles.angles[0];
		joint_angles.angles[1] = 0;
		joint_angles.angles[2] = 0;

		pub.publish(joint_angles);

		loop_rate.sleep();
		ros::spinOnce();
	}

	return 0;
}