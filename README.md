# 'arduino_ros'
> The code in this repository can be used to control a **4-DOF Robotic Arm** with **Xbox Controller** and as well as
 **Autonomously using Inverse Kinematics**

### Steps To Control Robotic Arm using Xbox Controller
* Clone the repository
* Connect and configure the [Arduino for ROS](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup).
* Connect [Xbox Controller and Configure for ROS](http://wiki.ros.org/joy)
* Now open a terminal window and write *roscore* and hit enter.
* Open new terminal and go to directory where you cloned the repo and add path of the current directory by using:
  * *$source ./devel/setup.bash*
* In the same terminal, use follwing set of commands to compile, run the node for Xbox and also for serial communication with arduino:
  * *$catkin_make arduino_ros_firmware_xbox*
  * *$catkin_make arduino_ros_firmware_xbox-upload*
  * *$rosrun rosserial_python serial_node.py /dev/ttyACM0*

### Steps to Control Robot Autonomously using Inverse Kinematics
* Open a terminal and start ROS master node by executing *roscore*
* Open new terminal and go to directory where you cloned the repo and add path of the current directory by using:
  * *$source ./devel/setup.bash*
* Now, fire new terminal and use following set of commands to compile and burn code on arduino:
 * *$catkin_make arduino_ros_firmware_servo_angles*
 * *$catkin_make arduino_ros_firmware_servo_angles-upload*
* In the same terminal, run node for Autonomous Control of the manipulator by using this command:
 * *$rosrun arduino_ros arm_angles*
* To establish communication with arduino, open new terminal and use:
 * *$rosrun rosserial_python serial_node.py /dev/ttyACM0*
* Flow of Autonomous Control:
 * When you run the node for Autonomous Control, it asks for type of object(1/2).
 * Depending upon the type of the object, the destination of the object is set.
