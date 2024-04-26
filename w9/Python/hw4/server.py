import socket
from time import *

f = open('bod.txt','w')

sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sd.bind(('127.0.0.1',1234))
sd.listen(1)
conn, addr = sd.accept()
data = conn.recv(1024).decode()
print(f'Received: {data}')
f.write(data)