#!/usr/bin/python3
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import LifecycleNode
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument

import lifecycle_msgs.msg
import os

def generate_launch_description():

    qt_viewer_dir = os.path.join(get_package_share_directory('qt_viewer'), 'params', 'UI.yaml')
                     
    qt_viewer_node = LifecycleNode(package='qt_viewer',
                                executable='qt_viewer_node',
                                name='qt_viewer_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='',
                                parameters=[qt_viewer_dir],
                                )


    return LaunchDescription([
        qt_viewer_node,
    ])

