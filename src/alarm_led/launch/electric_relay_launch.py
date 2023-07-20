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

    electric_relay_dir = os.path.join(get_package_share_directory('electric_relay'), 'params', 'params.yaml')
                     
    electric_relay_node = LifecycleNode(package='electric_relay',
                                executable='electric_relay_node',
                                name='electric_relay_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='',
                                parameters=[
                                electric_relay_dir
                                ],
                                )



    return LaunchDescription([
        electric_relay_node,
    ])

