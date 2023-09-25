import sys
import os

import socket

def main():

    serverIP = "192.168.137.4"
    serverPort = 8888
    bufferSize = 576

    msg = "Hello"
    bytesToSend = str.encode(msg)

    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    UDPClientSocket.sendto(bytesToSend, (serverIP, serverPort))

    print("Sent: {}".format(msg))

    msgFromServer = UDPClientSocket.recvfrom(bufferSize)

    print("Received: {}".format(msgFromServer))

    return 0


if __name__ == "__main__":

    sys.exit(main())
