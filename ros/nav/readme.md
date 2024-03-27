# Navigation of Bot

In ROS2, **keeping track of frames** is crucial for various operations such as robot localization, sensor data processing, and navigation. This involves understanding the robot's position relative to its environment, other robots, or specific points of interest. The TF2 package in ROS2 facilitates this by computing 3D translations and rotations between frames.

1. **Defining Frames**: Three essential frames include `map`, `scan` (lidar), and `base_link`. These frames are defined in the URDF (Unified Robot Description Format), specifying their relationships and transformations.

2. **URDF Visualization**: Use the URDF to visualize the robot's structure and frames. The `urdf_tutorial` package provides tools for this purpose.

```bash
sudo apt install ros-humble-urdf-tutorial
ros2 launch urdf_tutorial display.launch.py model:=/home/vivek/own_robot/my_robot.urdf
```

3. **Robot State Publisher**: ROS2 provides the `robot_state_publisher` node, which computes and publishes transforms based on URDF and joint state data from the robot's controller.

## Odometry

**Odometry** is crucial for localizing the robot's position based on its motion:

- **Basic Odometry**: Utilize wheel encoders to estimate velocity and position by integrating wheel movement. Publish odometry data on the `odom` topic and the `odom` to `base_link` transform on the `/tf` topic.

- **ROS2 Control Framework**: Utilize the `diff_drive_controller` within the ROS2 Control framework to handle closed-loop control, PID, and odometry publication.

- **Sensor Fusion**: For improved accuracy, integrate data from multiple sensors using packages like `robot_localization`. This includes incorporating IMU data and merging it with odometry for better localization.

## Sensor Data Handling

- **LIDAR Data**: Read LIDAR data and publish it on the `/scan` topic using the `sensor_msgs/LaserScan` message type.

- **Camera Data**: Add a camera link in the URDF and publish images on the camera topic using `sensor_msgs/Image`.

- **Minimal Sensor Setup**: For basic navigation, wheel encoders and LIDAR are sufficient. Use wheel encoder data for odometry and LIDAR data for environment sensing.

## Navigation Setup

- **Install SLAM Package**: Install the `slam_toolbox` package for Simultaneous Localization and Mapping.

```bash
sudo apt install ros-humble-slam-toolbox
```

- **Start Navigation**: Launch navigation components using `nav2_bringup`, including map server setup and configuration.

```bash
ros2 launch nav2_bringup navigation_launch.py use_sim_time:=True
ros2 run nav2_map_server map_saver_cli -f maps/custom_robot
```

- **Start SLAM Toolbox**: Utilize SLAM toolbox nodes for online mapping and localization.

```bash
ros2 launch slam_toolbox online_async_launch.py use_sim_time:=True
```

- **Visualize in RViz**: Launch RViz for visualization and configuration of navigation components.

```bash
ros2 run rviz2 rviz2
```

- **Control Robot**: Use teleoperation nodes like `turtlebot3_teleop` to control the robot for map creation.

```bash
ros2 run turtlebot3_teleop teleop_keyboard
```

---

This structured approach provides a comprehensive overview of the navigation setup in ROS2, covering frame definitions, odometry, sensor data handling, and navigation component setup. Let me know if you need further clarification or adjustments!