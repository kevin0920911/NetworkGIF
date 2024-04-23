import socket
import time

HOST,PORT = "127.0.0.1",1234
serverSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
serverSocket.bind((HOST,PORT))
print("UDP Server up and listening...")
while True:
    start = time.time()
    data = serverSocket.recv(1024)
    end = time.time()
    print(f"recv:{data.decode()} rate: {len(data)/(end-start)}")
    print("===============================")