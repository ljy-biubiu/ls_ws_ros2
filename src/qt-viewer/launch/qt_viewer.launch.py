import launch
import launch.actions
import launch.substitutions
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='qt_viewer',
            executable='qt_viewer_node',
            name='qt_viewer',
            parameters=[
                {'use_sim_time': False}
            ],
            output='screen'
        )
    ])
