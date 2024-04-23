import socket

HOST,PORT = "127.0.0.1",int(input("Enter port: "))
serverSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
serverSocket.bind((HOST,PORT))

while True:
    message ,ip = serverSocket.recvfrom(1024)
    print(f"Client IP: {ip}")
    print(f"Message: {message.decode()}")
    print("===============================")
