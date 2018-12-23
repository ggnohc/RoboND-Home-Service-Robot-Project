#!/bin/sh

#xterm  -e "source devel/setup.bash; export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/world/home_service_robot.world"; roslaunch turtlebot_gazebo turtlebot_world.launch" &
#sleep 10
#xterm  -e "source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:="$(pwd)/src/slam_gmapping/gmapping/launch/slam_gmapping_pr2.launch"  " &
#sleep 5
#xterm  -e "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
#sleep 5
#xterm  -e "source devel/setup.bash; rosrun wall_follower wall_follower"


xterm -e " cd /home/workspace/catkin_ws; catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/U-world/U-world.world" &
sleep 10 
#xterm -e "roslaunch gmapping.launch" &   #where do i get the gmapping.launch
xterm  -e "cd /home/workspace/catkin_ws; source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch custom_gmapping_launch_file:="/home/workspace/catkin_ws/src/slam_gmapping/gmapping/launch/slam_gmapping_pr2.launch"  " &
sleep 5
xterm -e " cd /home/workspace/catkin_ws; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e " cd /home/workspace/catkin_ws; source devel/setup.bash; rosrun wall_follower wall_follower" &
