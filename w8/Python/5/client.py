import socket

DATA = "I Love Python!!!!"
HOST,PORT = "127.0.0.1",1234
IP,CLIPORT = "127.0.0.1",3456

clientSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
clientSocket.bind((IP,CLIPORT))
clientSocket.connect((HOST,PORT))
clientSocket.send(DATA.encode())

print(f"Message send: {DATA}")