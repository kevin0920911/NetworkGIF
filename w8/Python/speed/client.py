import socket
import time

HOST,PORT = "127.0.0.1",1234
DATA = "I don't know what to send"
sd = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sd.connect((HOST,PORT))

while True:
    rate = int(input("Enter rate: "))
    sendTime = 1/rate
    for i in range(10):
        sd.send(DATA.encode())
        print(f"Message send: {DATA}")
        time.sleep(sendTime)