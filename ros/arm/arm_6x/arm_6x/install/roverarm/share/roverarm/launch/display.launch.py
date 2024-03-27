import launch
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_description = get_package_share_directory('roverarm')
    urdf_file = os.path.join(pkg_description, "urdf", 'roverarm.urdf')

    return LaunchDescription([
        DeclareLaunchArgument('model', default_value=urdf_file, description='Path to URDF file'),

        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            namespace='',
            output='screen',
            parameters=[{'use_sim_time': False}],
            arguments=[LaunchConfiguration('model')],
        ),

        Node(
            package='joint_state_publisher_gui',
            executable='joint_state_publisher_gui',
            name='joint_state_publisher_gui',
            namespace='',
            output='screen',
        ),

        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='tf_footprint_base',
            namespace='',
            output='screen',
            arguments=['0', '0', '0', '0', '0', '0', 'base_link', 'base_footprint'],
        ),

        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz',
            namespace='',
            output='screen',
            arguments=['-d', os.path.join(pkg_description, 'rviz', 'urdf.rviz')],
        ),
    ])