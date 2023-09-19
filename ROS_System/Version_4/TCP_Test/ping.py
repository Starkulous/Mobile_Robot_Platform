import sys
import os

import socket

def main():

    serverIP = "192.168.137.3"
    serverPort = 8888
    bufferSize = 576

    msg = "Hello"
    bytesToSend = str.encode(msg)

    TCPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)

    TCPClientSocket.connect((serverIP, serverPort)) 
    print("Connected to {}:{}".format(serverIP, serverPort))

    TCPClientSocket.sendall(bytesToSend)  
    print("Sent: {}".format(msg))

    msgFromServer = TCPClientSocket.recv(bufferSize)
    print("Received: {}".format(msgFromServer.decode()))
    
    return 0


if __name__ == "__main__":

    sys.exit(main())
