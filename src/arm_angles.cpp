#include "ros/ros.h"
#include "arduino_ros/data.h"
#include <cmath>

#define pi 3.14159265359

using namespace std;

const float l1 = 110;
const float l2 = 180;
float elbow_theta;
float shoulder_theta;
float base_theta;

float elbow_angle(double, double);
float shoulder_angle(double, double);

arduino_ros::data joint_angles;

int main(int argc, char **argv)
{
	ros::init(argc,argv,"joint_angle");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<arduino_ros::data>("angles",10000);
	
	ros::Rate loop_rate(10);

	while(ros::ok())
	{

		int status = 1,object_status = 0;
		bool isObject = false;

		cout<<"Initial Position"<<endl;
		joint_angles.angles[0] = 90;
		joint_angles.angles[1] = shoulder_angle(-92.0106, 220.989);
		joint_angles.angles[2] = elbow_angle(-92.0106, 220.989);
		//joint_angles.angles[3] = 180;

		pub.publish(joint_angles);

		cout<<"Type of object(1/2): ";
		cin>>object_status;

		if(object_status != 0)
			isObject = true;
		else
			isObject = false;

		
		if(isObject)
		{
			/*path_planning(status);
			if(status == 0)
			{
				cout<<"Initial Position"<<endl;
				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = shoulder_angle(-68.3324, 197.322);
				joint_angles.angles[2] = elbow_angle(-68.3324, 197.322);

				pub.publish(joint_angles);

				ros::Duration(4).sleep();

				status = 1;
			}*/

			if(status == 1)
			{
				cout<<"Picking The Object"<<endl;
				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = 360 + shoulder_angle(-280, -5.52026);
				joint_angles.angles[2] = elbow_angle(-280, -5.52026);
				//joint_angles.angles[3] = (double)180;

				pub.publish(joint_angles);
				ros::Duration(1).sleep();

				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = 360 + shoulder_angle(-280, -5.52026);
				joint_angles.angles[2] = elbow_angle(-280, -5.52026);
				//joint_angles.angles[3] = 0;

				pub.publish(joint_angles);
				ros::Duration(3).sleep();

				status = 2;
			}

			if(status == 2)
			{
				cout<<"Initial Position"<<endl;
				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = shoulder_angle(-92.0106, 220.989);
				joint_angles.angles[2] = elbow_angle(-92.0106, 220.989);				
				//joint_angles.angles[3] = (double)0;

				pub.publish(joint_angles);

				ros::Duration(4).sleep();

				status = 3;
			}

			if(status == 3)
			{
				cout<<"Placing The Object"<<endl;

				if(object_status == 1)
					joint_angles.angles[0] = 45;
				if(object_status == 2)
					joint_angles.angles[0] = 135;
				joint_angles.angles[1] = shoulder_angle(-92.0106, 220.989);
				joint_angles.angles[2] = elbow_angle(-92.0106, 220.989);
				//joint_angles.angles[3] = (double)0;

				pub.publish(joint_angles);
				ros::Duration(2).sleep();

				if(object_status == 1)
					joint_angles.angles[0] = 45;
				if(object_status == 2)
					joint_angles.angles[0] = 135;
				joint_angles.angles[1] = 360 + shoulder_angle(-280, -5.52026);
				joint_angles.angles[2] = elbow_angle(-280, -5.52026);
				//joint_angles.angles[3] = 0;

				pub.publish(joint_angles);
				ros::Duration(3).sleep();


				if(object_status == 1)
					joint_angles.angles[0] = 45;
				if(object_status == 2)
					joint_angles.angles[0] = 135;
				joint_angles.angles[1] = 360 + shoulder_angle(-280, -5.52026);
				joint_angles.angles[2] = elbow_angle(-280, -5.52026);
				//joint_angles.angles[3] = 180;
				pub.publish(joint_angles);
				ros::Duration(1).sleep();

				status = 1;
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