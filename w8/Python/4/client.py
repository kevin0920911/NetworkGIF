import socket

DATA = "I Love Python!!!!"
HOST,PORT = "127.0.0.1",1234

clientSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
clientSocket.connect((HOST,PORT))
clientSocket.send(DATA.encode())

print(f"Message send: {DATA}")