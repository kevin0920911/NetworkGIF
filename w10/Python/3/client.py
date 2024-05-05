import socket

"""
    Server Information
        IP: 127.0.0.1
        PORT: 1234
"""
IP,PORT = "127.0.0.1", 1234
# crete a socket connet to server
sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sd.connect((IP,PORT))
print(f"Connect to server {IP}:{PORT}")

while True:
    data = sd.recv(1024).decode()
    print(f"Server: {data}")
sd.close()