#!/bin/bash
# xhost +local:root
xhost +

# https://github.com/IntelRealSense/realsense-ros/issues/388

# -v /dev/bus/usb:/dev/bus/usb \
# -v /dev/input:/dev/input \

docker run -ti \
--gpus=all \
--privileged=true \
--cap-add=CAP_SYS_ADMIN \
--ipc=host \
-e QT_GRAPHICSSYSTEM=native \
-e QT_X11_NO_MITSHM=1 \
-v /dev:/dev \
-v /lib/modules:/lib/modules \
-v /tmp/.X11-unix:/tmp/.X11-unix \
-e DISPLAY=$DISPLAY \
-v $PWD/.ros:/root/.ros \
-v $PWD:/workspace \
-p 6006:6006 \
--name hsr-run rosudacity:latest \
/bin/bash
