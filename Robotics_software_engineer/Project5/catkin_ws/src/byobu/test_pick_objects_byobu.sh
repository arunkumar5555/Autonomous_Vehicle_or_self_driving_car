#!/bin/sh

cd /workspace/catkin_ws
USER=root

byobu new-session -d -s $USER

# gazebo windows
byobu rename-window -t $USER:0 'turtlebot_world'
byobu send-keys "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/workspace/catkin_ws/src/my_robot/worlds/house.world" C-m
sleep 7

byobu new-window -t $USER:1 -n 'amcl'
byobu send-keys "source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/workspace/catkin_ws/src/map/map.yaml" C-m
sleep 5

byobu new-window -t $USER:2 -n 'view_navigation'
byobu send-keys "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation_marker.launch" C-m
sleep 5

byobu new-window -t $USER:3 -n 'pick_objects'
byobu send-keys "source devel/setup.bash; rosrun add_markers cube_node" C-m
sleep 5

byobu new-window -t $USER:4 -n 'markers'
byobu send-keys "source devel/setup.bash; rosrun pick_objects pick_objects" C-m

# byobu new-window -t $USER:3 -n 'turtlebot_teleop'
# byobu send-keys "roslaunch turtlebot_teleop keyboard_teleop.launch" C-m

#byobu split-window -v
#byobu split-window -h

# Set default window as the dev split plane
byobu select-window -t $USER:1

# Attach to the session you just created
# (flip between windows with alt -left and right)
byobu attach-session -t $USER