import socket

"""
Proxy Server Information
"""
HOST = "127.0.0.1"
PORT = 1234

sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sd.connect((HOST, PORT))

while True:
    print("Which Service You Want to Use")
    print("1) DNS Query")
    print("2> Datetime Service")
    data = input().encode()
    sd.send(data)
    if data.decode() == "1":
        #DNS query
        data = input("Please Input IP (format: ask://a.b.c.d)").encode()
        sd.send(data)
        data = sd.recv(1024)
        print(data.decode())
    elif data.decode() == "2":
        #Date time
        data = sd.recv(1024)
        print(data.decode())
    else:
        #Invalid Data
        print(sd.recv().decode())
sd.close()