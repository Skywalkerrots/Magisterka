# Postęp

1. Pozycja robota tf - DONE
2. POINTCLOUD - narazie daje losowe dane
3. Odometria

 $ roscore
 
 $ rosrun rosserial_python serial_node.py /dev/ttyUSB0
 
 W paczce differential-drive/scripts
 
 $ roslaunch differential_drive my_robot_drive.launch
 
 Sterowanie kołami
 
 $ rosrun teleop_twist_keyboard teleop_twist_keyboard.py _speed:=0.5 _turn:=4


http://wiki.ros.org/teleop_twist_keyboard

http://wiki.ros.org/differential_drive/tutorials/setup

http://wiki.ros.org/differential_drive

4. kalibracja kamer

http://wiki.ros.org/camera_calibration/Tutorials/StereoCalibration

LINKI:

http://wiki.ros.org/global_planner

http://wiki.ros.org/nav_core

http://wiki.ros.org/navigation/Tutorials

http://wiki.ros.org/navigation/Tutorials/RobotSetup

http://wiki.ros.org/ROS/Tutorials
