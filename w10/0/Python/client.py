import socket
import time

"""
    Server Information
        IP: 127.0.0.1
        PORT: 1234
"""
IP, PORT = "127.0.0.1", 1234

# create UDP socket
sd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sd.connect((IP, PORT))
sd.setblocking(False)
print("Wait for 10 secs...")
time.sleep(10)

while True:
    try:
        sd.send(b"Hello World!")
        print("Send every 3 secs: Hello World!")
        time.sleep(3)
    except:
        pass