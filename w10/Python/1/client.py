import socket
import time

"""
    File 
        Input: abc.txt
        Output: client.txt
"""
fin = open("abc.txt", "r")
fout = open("client.txt", "w")

"""
    Client Information
        IP: 127.0.0.1
        PORT: 1234
"""
IP,PORT = "127.0.0.1", 1234

# Create a client socket
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect((IP,PORT))

# Set Non Blocking
clientSocket.setblocking(False)

EOF = False
while True:
    try:
        data = clientSocket.recv(1024).decode()
        print(f"Server: {data}")
        if EOF and data == "END": break
        elif EOF: continue
        fout.write(data)
    except:
        pass
    try:
        data = fin.readline()
        if not data: raise EOFError
        clientSocket.send(data.encode())
        print(f"Client: {data}")
    except EOFError:   
        EOF = True
        print(f"Client: END")
        clientSocket.send(b'END')
    time.sleep(1)
fin.close()
fout.close()
# Close the connection
clientSocket.close()
fout.close()
fin.close() 