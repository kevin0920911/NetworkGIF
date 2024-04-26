import socket

DATA = "I Love Python!"

serversd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversd.bind(('127.0.0.1', 1234))
serversd.listen(5)
conn, addr = serversd.accept()
buffer = conn.recv(1024).decode()
print(f'Received: {buffer}')
conn.send(DATA.encode())
print(f'Sent: {DATA}')
