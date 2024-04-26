import socket

DATA = "I Love Python!"

sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sd.connect(('127.0.0.1', 1234))
sd.send(DATA.encode())
print(f'Sent: {DATA}')
buffer = sd.recv(1024).decode()
print(f'Received: {buffer}')