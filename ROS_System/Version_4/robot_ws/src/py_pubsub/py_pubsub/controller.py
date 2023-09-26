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
        
        TCPClientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverPort = 8888
        bufferSize = 576

        if(msg.data[0] == 1.0):
            serverIP = "192.168.137.3"
            msg = "B"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend) 
            
            serverIP = "192.168.137.4"
            msg = "B"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)
            
        elif(msg.data[1] == 1.0):
            serverIP = "192.168.137.3"
            msg = "R"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

            serverIP = "192.168.137.4"
            msg = "R"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

        elif(msg.data[3] == 1.0):
            serverIP = "192.168.137.3"
            msg = "L"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

            serverIP = "192.168.137.4"
            msg = "L"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

        elif(msg.data[4] == 1.0):
            serverIP = "192.168.137.3"
            msg = "F"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

            serverIP = "192.168.137.4"
            msg = "F"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

        elif(msg.data[6] == 1.0):
            serverIP = "192.168.137.3"
            msg = "N"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

            serverIP = "192.168.137.4"
            msg = "N"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

        elif(msg.data[7] == 1.0):
            serverIP = "192.168.137.3"
            msg = "P"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

            serverIP = "192.168.137.4"
            msg = "P"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

        else:
            serverIP = "192.168.137.3"
            msg = "S"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)

            serverIP = "192.168.137.4"
            msg = "S"
            bytesToSend = str.encode(msg)
            TCPClientSocket.connect((serverIP, serverPort))
            TCPClientSocket.sendall(bytesToSend)


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