# 'arduino_ros'
> The code in this repository can be used to control a **4-DOF Robotic Arm** with **Xbox Controller** and as well as
 **Autonomously using Inverse Kinematics**

### Steps To Control Robotic Arm using Xbox Controller
* Clone the repository
* Connect the Arduino
* Connect Xbox Controller and Confugure for [ROS](http://wiki.ros.org/joy)
* Now open a terminal window and write *roscore* and hit enter.
* Open new terminal and go to directory and add path of the current directory by using
  * > $source ./devel/setup.bash
* In the same terminal, use follwing set of commands to compile and run the node for Xbox.
  * > $catkin_make arduino_ros_firmware_xbox
  * > $catkin_make arduino_ros_firmware_xbox-upload
  * > $rosrun rosserial_python serial_node.py /dev/ttyACM0
