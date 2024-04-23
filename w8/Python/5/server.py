import socket

HOST,PORT = "127.0.0.1",1234

serverSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

serverSocket.bind((HOST,PORT))
print("UDP Server up and listening...")

while True:
    data, ip = serverSocket.recvfrom(1024)
    print(f"Client IP: {ip}")
    print(f"Message: {data.decode()}")
    print("===============================")