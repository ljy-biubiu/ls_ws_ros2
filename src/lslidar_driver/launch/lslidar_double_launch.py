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

    driver_dir_1 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_1.yaml')
    driver_dir_2 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_2.yaml')
    driver_dir_3 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_3.yaml')
    driver_dir_4 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_4.yaml')
    driver_dir_5 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_5.yaml')
    driver_dir_6 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_6.yaml')
    driver_dir_7 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_7.yaml')
    driver_dir_8 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_8.yaml')
    driver_dir_9 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_9.yaml')
    driver_dir_10 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_10.yaml')
    driver_dir_11 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_11.yaml')
    driver_dir_12 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_12.yaml')
    driver_dir_13 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_13.yaml')
    driver_dir_14 = os.path.join(get_package_share_directory('lslidar_driver'), 'params', 'lsn301_14.yaml')
                     
    driver_node_1 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_1',
                                parameters=[driver_dir_1],
                                )

    driver_node_2 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_2',
                                parameters=[driver_dir_2],
                                )


    driver_node_3 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_3',
                                parameters=[driver_dir_3],
                                )

    driver_node_4 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_4',
                                parameters=[driver_dir_4],
                                )

    driver_node_5 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_5',
                                parameters=[driver_dir_5],
                                )

    driver_node_6 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_6',
                                parameters=[driver_dir_6],
                                )    

    driver_node_7 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_7',
                                parameters=[driver_dir_7],
                                )

    driver_node_8 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_8',
                                parameters=[driver_dir_8],
                                )  

    driver_node_9 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_9',
                                parameters=[driver_dir_9],
                                )

    driver_node_10 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_10',
                                parameters=[driver_dir_10],
                                )                     

    driver_node_11 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_11',
                                parameters=[driver_dir_11],
                                )     

    driver_node_12 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_12',
                                parameters=[driver_dir_12],
                                )                     

    driver_node_13 = LifecycleNode(package='lslidar_driver',
                                executable='lslidar_driver_node',
                                name='lslidar_driver_node',		#设置激光数据topic名称
                                output='screen',
                                emulate_tty=True,
                                namespace='lidar_13',
                                parameters=[driver_dir_13],
                                )     

    driver_node_14 = LifecycleNode(package='lslidar_driver',
                            executable='lslidar_driver_node',
                            name='lslidar_driver_node',		#设置激光数据topic名称
                            output='screen',
                            emulate_tty=True,
                            namespace='lidar_14',
                            parameters=[driver_dir_14],
                            )     
                                

    rviz_dir = os.path.join(get_package_share_directory('lslidar_driver'), 'rviz', 'lslidar.rviz')

    rviz_node = Node(
        package='rviz2',
        namespace='',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_dir],
        output='screen')

    return LaunchDescription([
        driver_node_1,
        driver_node_2,
        driver_node_3,
        driver_node_4,
        driver_node_5,
        driver_node_6,
        driver_node_7,
        driver_node_8,
        driver_node_9,
        driver_node_10,
        driver_node_11,
        driver_node_12,
        driver_node_13,
        driver_node_14,
        rviz_node,
    ])

