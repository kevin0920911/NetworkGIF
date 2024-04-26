import socket 
from time import *

f = open('alice.jpg','rb')

sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sd.connect(('127.0.0.1', 1234))
for i in f.readlines():
    sd.send(i)
    print(f'Sent: {i}')
    sleep(0.1)
sd.send('END'.encode())
sd.close()