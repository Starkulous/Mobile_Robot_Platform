import os
import sys

import array
import struct

from fcntl import ioctl

import rclpy

from rclpy.node import Node
from std_msgs.msg import Float32MultiArray

verbose = False


class ControllerSubscriber(Node):
    def __init__(self):
        super().__init__('controller')

        self.subscription = self.create_subscription(Float32MultiArray, 'joystick', self.listener_callback, 10)

        self.subscription

        return

    def listener_callback(self, msg):

        self.get_logger().info("Received: {}".format(msg.data))

        return


    def __del__(self):

        return



def main(args=None):

    rclpy.init(args=args)

    controller_subscriber = ControllerSubscriber()

    rclpy.spin(controller_subscriber)

    controller_subscriber.destroy_node()

    rclpy.shutdown()

    return 0


if __name__ == "__main__":

    sys.exit(main())