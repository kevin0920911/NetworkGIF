# -*- coding: utf-8 -*-

import socket
import time


HOST = '127.0.0.1'
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(5)

print('server start at: %s:%s' % (HOST, PORT))


while True:
    print('wait for connection...')

    conn, addr = s.accept()
    print('connected by ' + str(addr))
    outdata = time.ctime()
    conn.send(outdata.encode())
    conn.close()
    print(f"Server send: {outdata}")
s.close()