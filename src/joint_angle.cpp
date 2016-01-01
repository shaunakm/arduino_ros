#include "ros/ros.h"
#include "arduino_ros/data.h"
#include <cmath>

#define PI 3.1415927

using namespace std;

const float shoulder_link = 100;
const float elbow_link = 150;
float elbow_theta;
float shoulder_theta;

float elbow_angle(double, double);
float shoulder_angle(double, double);

arduino_ros::data joint_angles;

int main(int argc, char **argv)
{
	ros::init(argc,argv,"joint_angle");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<arduino_ros::data>("angles",100);
	ros::Rate loop_rate(10);

	while(ros::ok())
	{
		double pos_x, pos_y;
		cout<<"Enter the x and y position in mm: ";
		cin>>pos_x>>pos_y;

		joint_angles.angles[0] = 90.0; 
		joint_angles.angles[1] = shoulder_angle(pos_x, pos_y);
		joint_angles.angles[2] = elbow_angle(pos_x, pos_y);

		pub.publish(joint_angles);

		loop_rate.sleep();
		ros::spinOnce();
	}

	return 0;
}

float elbow_angle(double x, double y)
{
	elbow_theta = atan2((double)(sqrt(1-(pow((pow(x,2)+pow(y,2)-pow(shoulder_link,2)-pow(elbow_link,2))/(pow(x,2)+pow(y,2)),2)))),
		(double)((pow(x,2)+pow(y,2)-pow(shoulder_link,2)-pow(elbow_link,2))/(pow(x,2)+pow(y,2))));
	//cout<<(180*elbow_theta/3.14159)<<endl;

	elbow_theta = 180 * elbow_theta / PI;

	return elbow_theta;
}

float shoulder_angle(double x, double y)
{
	shoulder_theta = atan2(y,x) - atan2(elbow_link*sin(elbow_angle(x,y)),
		(shoulder_link + elbow_link*cos(elbow_angle(x,y))));

	shoulder_theta = 180 * shoulder_theta / PI;

	return shoulder_theta;
}