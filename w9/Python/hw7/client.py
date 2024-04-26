import socket 
from time import *

f = open('alice.jpg','rb')

sd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sd.connect(('127.0.0.1', 1234))
while True:
    data = f.read(1024)
    if not data:
        break
    sd.send(data)
    print(f'Sent: {data}')
    
sd.send('END'.encode())
sd.close()