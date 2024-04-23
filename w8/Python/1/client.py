import socket

DATA = "I Love Python!!!!"
HOST,PORT = "127.0.0.1",1234

clientSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
clientSocket.sendto(DATA.encode(),(HOST,PORT))

print(f"Message send: {DATA}")