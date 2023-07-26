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

        if(msg.data[0] == 1.0):
            serverIP = "192.168.137.3"
            msg = "reverse"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
            
            serverIP = "192.168.137.4"
            msg = "reverse"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
            
        elif(msg.data[1] == 1.0):
            serverIP = "192.168.137.3"
            msg = "right"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

            serverIP = "192.168.137.4"
            msg = "right"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

        elif(msg.data[3] == 1.0):
            serverIP = "192.168.137.3"
            msg = "left"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

            serverIP = "192.168.137.4"
            msg = "left"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

        elif(msg.data[4] == 1.0):
            serverIP = "192.168.137.3"
            msg = "forward"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

            serverIP = "192.168.137.4"
            msg = "forward"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

        elif(msg.data[6] == 1.0):
            serverIP = "192.168.137.3"
            msg = "decrease"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

            serverIP = "192.168.137.4"
            msg = "decrease"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

        elif(msg.data[7] == 1.0):
            serverIP = "192.168.137.3"
            msg = "increase"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

            serverIP = "192.168.137.4"
            msg = "increase"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

        else:
            serverIP = "192.168.137.3"
            msg = "stop"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

            serverIP = "192.168.137.4"
            msg = "stop"
            bytesToSend = str.encode(msg)
            UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))
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