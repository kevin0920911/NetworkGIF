import socket
import time

"""
    Server Information
        IP: 127.0.0.1
        PORT: 1234
"""
IP, PORT = "127.0.0.1", 1234

# create UDP socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind((IP, PORT))
server.setblocking(False)

while True:
    try:
        data, addr = server.recvfrom(1024)
        print(f"Received: {data.decode()} from {addr}")
    except:
        pass