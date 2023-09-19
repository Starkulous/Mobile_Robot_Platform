#!/bin/bash
source /opt/ros/foxy/setup.bash
source /home/joe/robot_ws/install/setup.bash
sudo sh -c 'echo 1 >/sys/module/bluetooth/parameters/disable_ertm'
ros2 launch py_pubsub robot_launch.py 
