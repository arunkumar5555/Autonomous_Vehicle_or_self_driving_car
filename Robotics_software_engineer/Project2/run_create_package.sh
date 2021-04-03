

# Create and initialize a catkin_ws

mkdir -p /workspace/catkin_ws/src
cd /workspace/catkin_ws/src
catkin_init_workspace

# Navigate to the src directory of your catkin_ws and create the my_robot package:

cd /workspace/catkin_ws/src/
catkin_create_pkg my_robot

# Next, create a worlds directory and a launch directory, that will further define 
# the structure of your package:

cd /workspace/catkin_ws/src/my_robot/
mkdir launch
mkdir worlds

mkdir urdf

