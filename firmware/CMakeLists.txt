cmake_minimum_required(VERSION 2.8.3)

include_directories(${ROS_LIB_DIR})

# Remove this if using an Arduino without native USB (eg, other than Leonardo)
#add_definitions(-DUSB_CON)

generate_arduino_firmware(hello
  SRCS chatter.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(servo
  SRCS servo.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(button_servo
  SRCS button_servo.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(blink
  SRCS blink.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(servo_sub
  SRCS servo_sub.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(xbox_sub_arduino
  SRCS xbox_sub_arduino.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(xbox
  SRCS xbox.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(arm_servo_angles
  SRCS arm_servo_angles.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(ir_ranger
  SRCS ir_ranger.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)

generate_arduino_firmware(servo_angles
  SRCS servo_angles.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM0
)
