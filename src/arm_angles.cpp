#include "ros/ros.h"
#include "arduino_ros/data.h"
#include <cmath>

#define pi 3.14159265359

using namespace std;

const float l1 = 100;
const float l2 = 150;
float elbow_theta;
float shoulder_theta;
float base_theta;

float elbow_angle(double, double);
float shoulder_angle(double, double);
float base_angle(double, double);

arduino_ros::data joint_angles;

int main(int argc, char **argv)
{
	ros::init(argc,argv,"joint_angle");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<arduino_ros::data>("angles",10000);
	ros::Rate loop_rate(10);

	while(ros::ok())
	{

		int status = 0,object_status = 0;
		bool isObject = false;

		cout<<"Is object present?(1/0)";
		cin>>object_status;

		if(object_status == 1)
			isObject = true;
		else
			isObject = false;
		
		if(isObject)
		{
			if(status == 0)
			{
				cout<<"Initial Position"<<endl;
				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = shoulder_angle(-68.3324, 197.322);
				joint_angles.angles[2] = elbow_angle(-68.3324, 197.322);

				pub.publish(joint_angles);

				status = 1;
			}

			if(status == 1)
			{
				cout<<"Picking The Object"<<endl;
				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = 360 + shoulder_angle(-164.926, -78.5841);
				joint_angles.angles[2] = elbow_angle(-164.926, -78.5841);

				pub.publish(joint_angles);

				status = 2;
			}

			if(status == 2)
			{
				cout<<"Initial Position"<<endl;
				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = shoulder_angle(-68.3324, 197.322);
				joint_angles.angles[2] = elbow_angle(-68.3324, 197.322);

				pub.publish(joint_angles);

				status = 3;
			}

			if(status == 3)
			{
				cout<<"Placing The Object"<<endl;
				joint_angles.angles[0] = 45;
				joint_angles.angles[1] = 360 + shoulder_angle(-164.926, -78.5841);
				joint_angles.angles[2] = elbow_angle(-164.926, -78.5841);

				pub.publish(joint_angles);

				status = 0;
			}
			isObject = false;
		}
		loop_rate.sleep();
		ros::spinOnce();
	}

	return 0;
}

float elbow_angle(double x, double y)
{
	double c2 = (pow(x,2)+pow(y,2)-pow(l1,2)-pow(l2,2))/(2*l1*l2);

	elbow_theta = atan2(sqrt(1-pow(c2,2)),c2);
	//cout<<(180*elbow_theta/3.14159)<<endl;

	elbow_theta = 180 * elbow_theta / pi;

	return elbow_theta;
}

float shoulder_angle(double x, double y)
{

	double k2 = l2 * sin(elbow_angle(x,y) * pi / 180);
	double k1 = l1 + l2 * cos(elbow_angle(x,y) * pi / 180);

	shoulder_theta = atan2(y,x) - atan2(k2, k1);

	shoulder_theta = 180 * shoulder_theta / pi;

	return shoulder_theta;
}
