import socket

def main():
    serverIP = '192.168.137.3'
    serverPort = 8888
    bufferSize = 576

    msg = "Hello"
    bytesToSend = msg.encode()

    TCPClientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        TCPClientSocket.connect((serverIP, serverPort))
        print("Connected to server")

        TCPClientSocket.sendall(bytesToSend)  

        received_data = TCPClientSocket.recv(bufferSize) 
        print("Received:", received_data.decode())

    except socket.error as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
