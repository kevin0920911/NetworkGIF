import socket
import time

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
serverSocket.setblocking(False)

# crete client socket
clientSocket = []
# Waiting for connteing (5 seconds)
start,end = time.time(),time.time()
while end-start < 5:
    try:
        conn, addr = serverSocket.accept()
        print(f"Connect to {addr}")
        conn.setblocking(False)
        clientSocket.append(conn)
    except:
        pass
    end = time.time()
time.sleep(5)
breaked = False
while True: 
    for i, client in enumerate(clientSocket):
        try:
            data = client.recv(1024).decode()
            print(f"({i}) {data}")
            for j,sock in enumerate(clientSocket):
                if j == i: continue
                n = sock.send(data.encode())
                if n == 0: 
                    breaked = True
                    break
            if breaked: break
        except:
            pass
    if breaked: break

for i in clientSocket:
    i.close()