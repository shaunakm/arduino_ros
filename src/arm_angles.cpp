/*
Aim: To calculate the 'Joint Angles' required using 'Inverse Kinematics' such that robotic arm reaches a given 
destination
Decription: Initially, the arm goes to the 'Initial Position' and waits for the user's input.
User has two choices(1/2) where he can place the object which is kept at the 'Source Position'.
Once the user presses 1/2, the robotic arm follows the that perticular path until the object reaches the destination.
'Joint Angles' are calculated using 'Inverse Kinematics' and publishes on the ROS Master node as '/angles'.
*/

#include "ros/ros.h"
#include "arduino_ros/data.h"
#include <cmath>

#define pi 3.14159265359

using namespace std;

const float l1 = 110;	//Link 1 length(Shoulder)
const float l2 = 180;	//Link 2 length(Elbow)
float elbow_theta;
float shoulder_theta;
float base_theta;

//Functions to calculate the joint angles.
float elbow_angle(double, double);
float shoulder_angle(double, double);

//Data type that will be published onto the ROS Master node(See in msg/data.msg)
arduino_ros::data joint_angles;

int main(int argc, char **argv)
{
	ros::init(argc,argv,"joint_angle");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<arduino_ros::data>("angles",10000);
	
	ros::Rate loop_rate(10);

	while(ros::ok())
	{
		//Path Planning algorithm

		int status = 1,object_status = 0;
		bool isObject = false;

		//When we power up the arm, arm goes to this position.
		cout<<"Initial Position"<<endl;
		joint_angles.angles[0] = 90;
		joint_angles.angles[1] = shoulder_angle(-92.0106, 220.989);
		joint_angles.angles[2] = elbow_angle(-92.0106, 220.989);

		pub.publish(joint_angles);

		//Asks user for the type of object.
		cout<<"Type of object(1/2): ";
		cin>>object_status;

		if(object_status != 0)
			isObject = true;
		else
			isObject = false;

		if(isObject)
		{

			if(status == 1)
			{
				//Source Position.
				cout<<"Picking The Object"<<endl;
				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = 360 + shoulder_angle(-264.336, -71.6075);
				joint_angles.angles[2] = elbow_angle(-264.336, -71.6075);

				pub.publish(joint_angles);
				ros::Duration(1).sleep();

				joint_angles.angles[0] = 90;
				joint_angles.angles[1] = 360 + shoulder_angle(-264.336, -71.6075);
				joint_angles.angles[2] = elbow_angle(-264.336, -71.6075);

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

				pub.publish(joint_angles);

				ros::Duration(4).sleep();

				status = 3;
			}

			if(status == 3)
			{
				//Destination Position depending upon the user's choice.
				cout<<"Placing The Object"<<endl;

				if(object_status == 1)
					joint_angles.angles[0] = 45;
				if(object_status == 2)
					joint_angles.angles[0] = 135;
				joint_angles.angles[1] = shoulder_angle(-92.0106, 220.989);
				joint_angles.angles[2] = elbow_angle(-92.0106, 220.989);
		
				pub.publish(joint_angles);
				ros::Duration(2).sleep();

				if(object_status == 1)
					joint_angles.angles[0] = 45;
				if(object_status == 2)
					joint_angles.angles[0] = 135;
				joint_angles.angles[1] = 360 + shoulder_angle(-264.336, -71.6075);
				joint_angles.angles[2] = elbow_angle(-264.336, -71.6075);

				pub.publish(joint_angles);
				ros::Duration(3).sleep();


				if(object_status == 1)
					joint_angles.angles[0] = 45;
				if(object_status == 2)
					joint_angles.angles[0] = 135;
				joint_angles.angles[1] = 360 + shoulder_angle(-264.336, -71.6075);
				joint_angles.angles[2] = elbow_angle(-264.336, -71.6075);
		
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