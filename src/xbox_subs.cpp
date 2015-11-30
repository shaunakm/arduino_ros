#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/String.h"
#include <sstream>

using namespace std;

std_msgs::String str_msg;

//sensor_msgs::Joy xbox;
long int axis;

void xboxCallBack(const sensor_msgs::Joy::ConstPtr& xboxmsg)
{
	//xbox = xboxmsg;
	axis = xboxmsg->axes[0];
	//cout<<axis<<" and ";
	//ROS_INFO("%d",xboxmsg->buttons);
	//ROS_INFO("chalne de dost..!!\n");
}

int main(int argc, char **argv)
{
	ros::init(argc,argv,"xbox_subs");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("joy",100,xboxCallBack);
	ros::Publisher pub = n.advertise<std_msgs::String>("controller_data",100);

	while(ros::ok())
	{
		if(axis == -1)
			str_msg.data = "rr";
		else if(axis == 1)
			str_msg.data = "rl";
		else
			str_msg.data = "null";

		cout<<axis<<" and ";
		//ROS_INFO("%d",xboxmsg->buttons);
		ROS_INFO("chalne de dost..!!\n");

		pub.publish(str_msg);

		ros::Rate loop_rate(10);
		loop_rate.sleep();

		ros::spinOnce();
	}
	return 0;
}