#!/bin/sh


USER=root

byobu new-session -d -s $USER

# gazebo windows
byobu rename-window -t $USER:0 'gazebo'
#byobu send-keys "gazebo" C-m

byobu new-window -t $USER:1 -n 'ros'
byobu send-keys "source /opt/ros/kinetic/setup.bash; roscore" C-m

byobu new-window -t $USER:2 -n 'rviz'
byobu send-keys "rosrun rviz rviz" C-m


#byobu split-window -v
#byobu split-window -h

# Set default window as the dev split plane
byobu select-window -t $USER:1

# Attach to the session you just created
# (flip between windows with alt -left and right)
byobu attach-session -t $USER
