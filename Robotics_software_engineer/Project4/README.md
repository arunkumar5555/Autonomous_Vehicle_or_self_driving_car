# Project 4: Map My World


- Db file generated: https://drive.google.com/file/d/1OCbd9_EqUUKv5pViZa8yz5WHtof79qLQ/view?usp=sharing


### Basic commands

    mkdir -p /workspace/catkin_ws/src
    cd workspace/catkin_ws/src
    catkin_init_workspace
    catkin_make

    roslaunch my_robot world.launch
    roslaunch my_robot teleop.launch
    roslaunch my_robot mapping.launch
    rtabmap-databaseViewer src/my_robot/rtabmap.db
    roslaunch my_robot localization.launch


    git clone https://github.com/ros-teleop/teleop_twist_keyboard
    git clone https://github.com/udacity/pgm_map_creator
    git clone https://github.com/turtlebot/turtlebot_simulator
    git clone https://github.com/udacity/robot_pose_ekf
    git clone https://github.com/udacity/odom_to_trajectory


### Docker

- https://github.com/facontidavide/ros-docker-gazebo
- https://github.com/Seanmatthews/ros-docker-gazebo

        sudo apt-get install -y usbutils
        docker build -f "Dockerfile" -t rosudacity:latest .
        bash run_docker.sh

        xhost +
        docker start mmw-run
        docker attach mmw-run


### Git

- https://github.com/udacity/RoboND-myrobot


### Models

- https://github.com/osrf/gazebo_models
- https://3dwarehouse.sketchup.com/


### Doc

- http://wiki.ros.org/
- http://answers.ros.org/
