#!/bin/bash

# Build the catkin_ws
#cd $(pwd)/../..; catkin_make

# Launch the nodes
#xterm  -e "source devel/setup.bash; export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/world/home_service_robot.world"; roslaunch turtlebot_gazebo turtlebot_world.launch" &
#sleep 10
#xterm  -e "source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
#sleep 5
#xterm  -e "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
#sleep 5
#xterm  -e "source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"

xterm -e "cd /home/workspace/catkin_ws; catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/U-world/U-world.world" &
sleep 15
#xterm -e "rosrun gmapping slam_gmapping" &
xterm -e "cd /home/workspace/catkin_ws; source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -e "cd /home/workspace/catkin_ws; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "cd /home/workspace/catkin_ws; source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch" &
