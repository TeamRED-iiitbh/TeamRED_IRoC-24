# import launch
# from launch import LaunchDescription
# from launch.actions import DeclareLaunchArgument
# from launch.substitutions import LaunchConfiguration, PythonExpression
# from launch_ros.actions import Node
# import os
# from ament_index_python.packages import get_package_share_directory

# def generate_launch_description():
#     pkg_description = get_package_share_directory('roverarm')
#     urdf_file = os.path.join(pkg_description, "urdf", 'roverarm.urdf')

#     return LaunchDescription([
#         DeclareLaunchArgument('model', default_value=urdf_file, description='Path to URDF file'),

#         # Include Gazebo launch
#         Node(
#             package='gazebo_ros',
#             executable='gzserver',
#             name='gazebo',
#             arguments=[
#                 '--verbose',  # Added for verbose output
#                 '-s', 'libgazebo_ros_init.so',
#                 '--ros-args', '--wait'],
#             output='screen',
#         ),

#         # Spawn model in Gazebo
#         Node(
#             package='gazebo_ros',
#             executable='spawn_entity.py',
#             name='spawn_roverarm',
#             arguments=[
            
#                 '-entity', 'roverarm',
#                 '-file', LaunchConfiguration('model'),
                
#             ],
#             output='screen',
#         ),

#         # Other nodes for robot state publishing, joint state publishing, and static transform publisher
#         Node(
#             package='robot_state_publisher',
#             executable='robot_state_publisher',
#             name='robot_state_publisher',
#             namespace='',
#             output='screen',
#             parameters=[{'use_sim_time': True}],
#             arguments=[LaunchConfiguration('model')],
#         ),

#         Node(
#             package='joint_state_publisher_gui',
#             executable='joint_state_publisher_gui',
#             name='joint_state_publisher_gui',
#             namespace='',
#             output='screen',
#         ),

#         Node(
#             package='tf2_ros',
#             executable='static_transform_publisher',
#             name='tf_footprint_base',
#             namespace='',
#             output='screen',
#             arguments=['0', '0', '0', '0', '0', '0', 'base_link', 'base_footprint'],
#         ),

#         # Fake joint calibration node (optional)
#         Node(
#             package='rostopic',
#             executable='rostopic',
#             name='fake_joint_calibration',
#             output='screen',
#             arguments=['pub', '/calibrated', 'std_msgs/Bool', 'true'],
#         ),
#     ])

#!usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import xacro
from launch_ros.actions import Node

def generate_launch_description():

    # Specify the name of the package and path to xacro file
    pkg_name = 'roverarm'
    file_subpath = os.path.join(get_package_share_directory(pkg_name),'urdf/roverarm.urdf')

    # Use xacro to process the file (optional, if needed)
    xacro_file = os.path.join(get_package_share_directory(pkg_name), file_subpath)
    # robot_description_raw = xacro.process_file(xacro_file).toxml()
    doc = xacro.parse(open(xacro_file))
    xacro.process_doc(doc)
    params = {'robot_description':doc.toxml()}

    # Configure the robot state publisher node
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        # parameters=[{'robot_description': file_subpath,  
                    # 'use_sim_time': True}]
        parameters= [params]
    )

    # Include Gazebo launch description (consider adding plugins if needed)
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(
            get_package_share_directory('gazebo_ros'), 'launch', 'gazebo.launch.py')),
        # Add Gazebo plugin launch arguments here (if applicable)
    )


    # Spawn entity using robot_description topic
    spawn_entity = Node(package='gazebo_ros', executable='spawn_entity.py',
                    arguments=['-topic', 'robot_description',  # Ensure topic name matches
                                '-entity', 'roverarm'],
                    output='screen')


    return LaunchDescription([
        gazebo,
        node_robot_state_publisher,
        spawn_entity
    ])

