#!/bin/sh

USER=root

byobu new-session -d -s $USER

# gazebo windows
byobu rename-window -t $USER:0 'turtlebot_world'
byobu send-keys "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" C-m

byobu new-window -t $USER:1 -n 'slam'
byobu send-keys "source devel/setup.bash; rosrun gmapping slam_gmapping" C-m

byobu new-window -t $USER:2 -n 'view_navigation'
byobu send-keys "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" C-m

byobu new-window -t $USER:3 -n 'turtlebot_teleop'
byobu send-keys "source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch" C-m

#byobu split-window -v
#byobu split-window -h

# Set default window as the dev split plane
byobu select-window -t $USER:3

# Attach to the session you just created
# (flip between windows with alt -left and right)
byobu attach-session -t $USER