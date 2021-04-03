# Project 3: Where I Am ?

### Basic commands

    mkdir -p /workspace/catkin_ws/src
    cd workspace/catkin_ws/src
    catkin_init_workspace
    catkin_make

    git clone https://github.com/ros-teleop/teleop_twist_keyboard
    git clone https://github.com/udacity/pgm_map_creator
    git clone https://github.com/turtlebot/turtlebot_simulator
    git clone https://github.com/udacity/robot_pose_ekf
    git clone https://github.com/udacity/odom_to_trajectory


### Docker

- https://github.com/facontidavide/ros-docker-gazebo
- https://github.com/Seanmatthews/ros-docker-gazebo


        sudo apt-get install -y usbutils
        docker build -f "Dockerfile" -t mrosmcl:latest .
        bash run_docker.sh


### Git

- https://github.com/udacity/RoboND-myrobot


### Models

- https://github.com/osrf/gazebo_models
- https://3dwarehouse.sketchup.com/


### Doc

- http://wiki.ros.org/
- http://answers.ros.org/


# Issue

## Failed to create map
- https://github.com/hyfan1116/pgm_map_creator/issues/1

        # change msgs/CMakeLists.txt to:
        set (msgs
        collision_map_request.proto
        # ${PROTOBUF_IMPORT_DIRS}/vector2d.proto
        # ${PROTOBUF_IMPORT_DIRS}/header.proto
        # ${PROTOBUF_IMPORT_DIRS}/time.proto
        )