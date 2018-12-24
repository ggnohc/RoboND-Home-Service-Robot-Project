#!/bin/sh

xterm -e " cd /home/workspace/catkin_ws; catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/U-world/U-world.world" &
sleep 10 
xterm -e "roslaunch gmapping.launch" &   #where do i get the gmapping.launch
sleep 5
xterm -e " cd /home/workspace/catkin_ws; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e " cd /home/workspace/catkin_ws; source devel/setup.bash; rosrun wall_follower wall_follower" &
