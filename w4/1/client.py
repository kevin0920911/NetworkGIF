# -*- coding: utf-8 -*-
import socket
import time

HOST = '127.0.0.1'
PORT = 7000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

for i in range(5):
    outdata = 'hello ' + str(i+1)
    print('send: ' + outdata)
    s.send(outdata.encode())
    
    indata = s.recv(1024)
    if len(indata) == 0: # connection closed
        s.close()
        print('server closed connection.')
        break
    print('recv: ' + indata.decode())

    time.sleep(1)
s.close()