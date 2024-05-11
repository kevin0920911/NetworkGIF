import socket
import select

"""
    Server information
        IP: 127.0.0.1
        PORT: 1234
"""
IP, PORT = "127.0.0.1", 1234
# Create a socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect((IP, PORT))
rsock = [server]

while True:
    readable,_, err= select.select(rsock, [], [])
    if err:
        print(err)
        break
    for sock in readable:
        try:
            data = sock.recv(1024)
            print(f"{data.decode()}")
            if data.decode() == "Server is full":
                server.close()
                break
        except Exception as e:
            print(e)
            server.close()
            break
