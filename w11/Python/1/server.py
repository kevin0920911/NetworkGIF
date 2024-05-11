import select
import socket
import datetime
import time

"""
    Server information
        IP: 127.0.0.1
        PORT: 1234
"""
IP, PORT = "127.0.0.1",1234

# Create a socket 
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((IP, PORT))
server.listen(5)

# List of sockets
Wsockets = [server]
Rsockets = []
while True:
    # Get the list of sockets which are ready to be read
    print("Waiting for clients")

    readables, writeables, error = select.select(Wsockets, Rsockets, [])
    if error:
        print(error)
        break
    for sock in readables:
        if sock is server:
            newClient, addr = server.accept()
            if len(Rsockets) >= 5:
                newClient.send(b"Server is full")
                newClient.close()
                break
            print(f"New client connected: {addr}")
            Rsockets.append(newClient)

    for sock in writeables:
        now = datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S")
        try:
            sock.send(f"{now}".encode())
            print(f"Send to clinet{Rsockets.find(sock)}: {now}")
        except Exception as e:
            print(e)
            sock.close()
            Rsockets.remove(sock)
    print(f"Client number: {len(Rsockets)}")
    time.sleep(1)