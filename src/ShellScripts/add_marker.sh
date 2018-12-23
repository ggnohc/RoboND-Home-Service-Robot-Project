#!/bin/sh
xterm -e " cd /home/workspace/catkin_ws; catkin_make; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/U-world/U-world.world" &
sleep 15 
xterm -e " cd /home/workspace/catkin_ws; source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch  map_file:=/home/workspace/catkin_ws/src/World/U-world/U-World-Map.yaml" &
sleep 5
xterm -e " cd /home/workspace/catkin_ws; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
#xterm -e " cd /home/workspace/catkin_ws; source devel/setup.bash; rosrun pick_objects pick_objects" &
#sleep 5
xterm -e " cd /home/workspace/catkin_ws; source devel/setup.bash; rosrun add_markers add_markers" &
