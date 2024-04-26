import socket

DATA = "[NCYU]"

sd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sd.bind(('127.0.0.1', 1234))

while True:
    buffer = sd.recv(5).decode()
    print(f'Received: {buffer}')
