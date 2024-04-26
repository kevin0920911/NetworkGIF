import socket
from time import *

sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sd.connect(('127.0.0.1', 1234))

file = open('alice.txt', 'r')
for line in file.readlines():
    sd.send(line.encode())
    print(f'Sent: {line}')
    sleep(1)