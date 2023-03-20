#!/bin/bash

#param_config_node = "ros2 run  params_config params_config_node" 
#web_node =  "ros2 run mywebsocket mywebsocket"
#lidar_driver_node = "ros2 run lidar_driver lidar_driver_node"
#camera_driver_node = "ros2 run camera_driver camera_driver_node"


export LD_LIBRARY_PATH=/home/ljy/ros2_ws/install/camera_driver/lib:$LS_LIBRARY_PATH

## Go to the destination directory.
cd /home/ljy/ros2_ws/

echo "Start a Tmux ros_session."

## Create a Tmux session "ros2_ws" in a window "window0" started in the background.
tmux new -d -s ros2_ws -n window0
#tmux send -t ros2_ws:window0 "tmux new-window -n window2 " ENTER

## Split the window to 4 panes.
#tmux split-window -h -t ros2_ws:window0
#tmux split-window -v -t ros2_ws:window0.0
#tmux split-window -v -t ros2_ws:window0.2

tmux send -t ros2_ws:window0.0 "tmux split-window -h -t ros2_ws:window0" ENTER
tmux send -t ros2_ws:window0.0 "tmux split-window -v -t ros2_ws:window0.0 " ENTER
tmux send -t ros2_ws:window0.0 "tmux split-window -v -t ros2_ws:window0.2" ENTER

tmux send -t ros2_ws:window0.0 "tmux new-window -n window1 " ENTER
tmux send -t ros2_ws:window0.0 "tmux split-window -h -t ros2_ws:window1" ENTER
tmux send -t ros2_ws:window0.0 "tmux split-window -v -t ros2_ws:window1.0 " ENTER
tmux send -t ros2_ws:window0.0 "tmux split-window -v -t ros2_ws:window1.2" ENTER


## Run the ROS programs sequentially.
#tmux send -t ros2_ws:window0.0 "tmux select-window -t window0.0 " ENTER
tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window0.0 \"clear && source install/setup.bash && sleep 1 && ros2 run  params_config params_config_node \" ENTER " ENTER
tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window0.1 \"source install/setup.bash && sleep 2 && ros2 run mywebsocket mywebsocket \" ENTER " ENTER
tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window0.3 \"source install/setup.bash && sleep 3 && ros2 run  qt_viewer qt_viewer_node \" ENTER " ENTE
tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window0.2 \"source install/setup.bash && sleep 4  \" ENTER " ENTER
#tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window0.3 \"source install/setup.bash && sleep 3 && ros2 run  qt_viewer qt_viewer_node \" ENTER " ENTER

tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window1.0 \"source install/setup.bash && sleep 5 && ros2 run lidar_driver lidar_driver_node  \" ENTER " ENTER
tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window1.1 \"source install/setup.bash && sleep 6 && ros2 run  camera_driver camera_driver_node \" ENTER " ENTER
tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window1.2 \"source install/setup.bash && sleep 6 && ros2 run monitor monitor_node \" ENTER " ENTER
tmux send -t ros2_ws:window0.0 "tmux send -t ros2_ws:window1.3 \"source install/setup.bash \" ENTER " ENTER


tmux a -t ros2_ws


#tmux new -d -s ros2_ws -n window1
#tmux new-window -s ros2_ws -n window1
#tmux select-window -t window1

## Split the window to 4 panes.
#tmux split-window -h -t window1
#tmux split-window -v -t window1.0
#tmux split-window -v -t window1.2

#tmux send -t ros2_ws:window1.0 "source setup.bash " ENTER
#tmux send -t ros2_ws:window1.1 "source setup.bash " ENTER
#tmux send -t ros2_ws:window1.2 "source setup.bash " ENTER
#tmux send -t ros2_ws:window1.3 "source setup.bash " ENTER



