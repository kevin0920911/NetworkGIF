# -*- coding: utf-8 -*-

import socket

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

    while True:
        indata = conn.recv(1024)
        if indata.decode() == ".": # connection closed
            conn.close()
            break
        print(f"Server recveive: {indata.decode()}")
s.close()