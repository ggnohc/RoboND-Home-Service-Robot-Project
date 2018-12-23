#!/bin/sh
#xterm  -e  " gazebo " &
#sleep 5
xterm  -e  "killall gazebo & killall gzserver & killall gzclient;  source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
#xterm  -e  " rosrun rviz rviz"
