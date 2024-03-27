#!/usr/bin/env python3
import rclpy 
from rclpy.node import Node

import math
from tf2_msgs.msg import TFMessage
from sensor_msgs.msg import JointState
from geometry_msgs.msg import Twist


class Move_end(Node):
    def __init__(self):
        super().__init__('move_the_end_effector')
        self.publisher = self.create_publisher(JointState,'/joint_states',10)
        time_period = 0.5
        self.timer = self.create_timer(time_period,self.joint_callback_fk)
        self.i = 0
        self.joint_names =  ['joint1','joint2','joint3','joint4','joint5','joint6']
        self.goal = [0,0,0,0,0,0]
    def joint_callback_fk(self,goal):
        Joint_State_msg = JointState()
        Joint_State_msg.name = self.joint_names
        Joint_State_msg.position = self.goal
        while rclpy.ok():
            Joint_State_msg.header.stamp=Node.get_clock().now().to_msg()
        
            self.publisher.publish(Joint_State_msg)

def main():
    move = Move_end()
    move.joint_callback_fk([0.2,0.3,0.4,0.5,0.6])
    rclpy.shutdown()

if __name__ =="__main__":
    main

