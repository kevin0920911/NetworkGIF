import socket
import time

"""
    File 
        Input: def.txt
        Output: server.txt
"""
fin = open("def.txt", "r")
fout = open("server.txt", "w")

"""
    Server Information
        IP: 127.0.0.1
        PORT: 1234
"""
IP,PORT = "127.0.0.1", 1234


# crete a server socket
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind((IP,PORT))
serverSocket.listen(5)

# Accept the client connection
clientSocket, address = serverSocket.accept()

# Set Non Blocking
clientSocket.setblocking(False)
serverSocket.setblocking(False)



EOF = False
while True:
    try:
        data = clientSocket.recv(1024).decode()
        print(f"Client: {data}")
        if EOF and data == "END": break
        elif EOF: continue
        fout.write(data)
    except :
        pass
    try:
        data = fin.readline()
        if not data: raise EOFError
        clientSocket.send(data.encode())
        print(f"Server: {data}")
    except EOFError:
        clientSocket.send(b'END')
        print(f"Server: END")
        EOF = True
    time.sleep(1)
# Close the connection
clientSocket.close()
serverSocket.close()