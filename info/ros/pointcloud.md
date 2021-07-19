# Point Cloud

Zbudowano paczkę "pointcloud". Wykorzytsujac komende:

$ catkin_create_pkg pointcloud roscpp sensor_msgs

Po nazwie dodawane są biblioteki wykorzystywane w pliku wykonywalnym.

Plik wykonywalny znajduje się w podfolderze src o nazwie Pointcloud.cpp

Plik generuje dane w postaci countera zwiększanego o 1.

## Odpalenie

$ roscore

W następnym terminalu przejsc do catkin_ws

$ source ./devel/setup.bash

$ rosrun pointcloud point_cloud

Podsłuchać publikuace dane mozna za pomoca

$ rostopic echo cloud

## Na podstawie

http://wiki.ros.org/navigation/Tutorials/RobotSetup/Sensors
