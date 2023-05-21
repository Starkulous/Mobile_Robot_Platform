import os
import sys

import socket

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
        
        UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
        serverPort = 8888
        bufferSize = 576

        if(msg[0] == 1):
            serverIP = "169.254.137.3"
            msg = "forward"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
            msgFromServer = UDPClientSocket.recvfrom(bufferSize)
            print("Received: {}".format(msgFromServer))

            serverIP = "169.254.137.4"
            msg = "forward"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
            msgFromServer = UDPClientSocket.recvfrom(bufferSize)
            print("Received: {}".format(msgFromServer))
        
        elif(msg[1] == 1):
            serverIP = "169.254.137.3"
            msg = "reverse"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
            msgFromServer = UDPClientSocket.recvfrom(bufferSize)
            print("Received: {}".format(msgFromServer))

            serverIP = "169.254.137.4"
            msg = "reverse"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
            msgFromServer = UDPClientSocket.recvfrom(bufferSize)
            print("Received: {}".format(msgFromServer))

        else:
            serverIP = "169.254.137.3"
            msg = "stop"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
            msgFromServer = UDPClientSocket.recvfrom(bufferSize)
            print("Received: {}".format(msgFromServer))

            serverIP = "169.254.137.4"
            msg = "stop"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
            msgFromServer = UDPClientSocket.recvfrom(bufferSize)
            print("Received: {}".format(msgFromServer))
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