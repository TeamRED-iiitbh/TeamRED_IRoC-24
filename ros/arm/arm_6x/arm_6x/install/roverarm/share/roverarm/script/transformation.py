#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import math
import numpy as np
import sympy as smp
from sympy.plotting import plot
from sympy import Function, sin ,cos

class Transform_frame(Node):
    def __init__(self):
        super().__init__('transform_frame')
        a = smp.symbols('a')
        alpha = smp.symbols('α')
        d = smp.symbols('d')
        theta = smp.symbols('θ')
        self.pi = 3.141592653436
    def transform(self,a, alpha, d, theta):
        theta = theta*(self.pi/180)
        alpha = alpha*(self.pi/180)
    
        t = np.array([[cos(theta), -1*sin(theta), 0, a],
                  [sin(theta)*cos(alpha), cos(theta)*cos(alpha), -sin(alpha), -sin(alpha)*d],
                  [sin(theta)*sin(alpha), cos(theta)*sin(alpha), cos(alpha), cos(alpha)*d],
                  [0, 0, 0, 1]])
        return t
    def dh_param(self):
        dh=np.array([[0,0,2*0.122,0],[0,90,0.1,90],[0,-90,0.1,90],[12,0,0,90],[12,0,0,90],[0,-90,0.2,90]])
        return dh

def main(args=None):
    rclpy.init(args=args)
    tf = Transform_frame()
    arr = tf.dh_param()
    for i in range(len(arr)):
        print(arr[i][0])
        tf1 = tf.transform(arr[i][0],arr[i][1],arr[i][2],arr[i][3])
        tf1 *=tf1
    print(tf1)
    print("hidfish")
    print(tf.transform(0,0,0,90))
    tf.destroy_node()
    rclpy.shutdown()
    
if __name__ =="__main__":
    main()

    
    


