# Transforamcja tf

Zbudowano paczkę "robot_setup_tf". Wykorzystano komende:

$ catkin_create_pkg robot_setup_tf roscpp tf geometry_msgs

Następnie utowrzono wewnątrz podfolderu src, dwa nody które mają rozmawiać ze sobą. Wykorzystano VSC do stworzenia plików tf_bradcaster.cpp oraz tf_listener.cpp.

Po napisaniu kodów należy utworzyć packiet.

$ catkin_make -> będac w folderze catkin_ws

## Odalenie nodów

Następnie w nowym terminalu

$ roscore

W następnym przejść do folderu catkin_ws.

$ source ./devel/setup.bash
$ rosrun robot_setup_tf tf_broadcaster

Analogicznie listener przejść do folderu catkin_ws.

$ source ./devel/setup.bash
$ rosrun robot_setup_tf tf_listener


### Na podstawie 

http://wiki.ros.org/navigation/Tutorials/RobotSetup/TF
