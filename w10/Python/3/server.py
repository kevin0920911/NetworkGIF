import socket
import time

"""
    The Data I want to send to the clinet
"""
DATA = "Something Smell"
FREQ = 1

"""
    Server Information
        IP: 127.0.0.1
        PORT: 1234
"""

IP,PORT = "127.0.0.1", 1234
# crete server socket
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind((IP,PORT))
serverSocket.listen(5)

# A list for client socket
clientSocket = []
sd,addr = serverSocket.accept()
clientSocket.append(sd)
print(f"Client {addr} connected")
serverSocket.setblocking(False)

while True:
    try:
        sd, addr = serverSocket.accept()
        clientSocket.append(sd)
        print(f"Client {addr} connected")
    except:
        pass
    disconnect = []
    for i,conn in enumerate(clientSocket):
        try:
            conn.send(DATA.encode())
        except ConnectionResetError:
            disconnect.append(i)
    for i in disconnect:
        clientSocket[i].close()
        clientSocket.pop(i)
        print(f"Client {i} disconnected")
    time.sleep(FREQ)
for i in clientSocket:
    i.close()