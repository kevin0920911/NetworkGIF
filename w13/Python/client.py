import socket 
import threading

PORT = [8888, 5678, 5679, 5680]
serverAddr, serverPort = "0.0.0.0" ,8888
sd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

def recvData():
    global serverPort
    global sd
    while True:
        data, addr = sd.recvfrom(1024)
        print(f"Received from {addr}: {data.decode()}")

setsockopt = sd.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sd.bind((serverAddr, serverPort))
print(sd)
threading.Thread(target=recvData).start()
while True:
    port = int(input(""))
    sd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sd.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    if port not in PORT:
        serverPort = 8888
        sd.bind((serverAddr, serverPort))
        print("Invalid port")
        continue
    elif port == 8888:
        serverPort = 8888
        sd.bind((serverAddr, serverPort))
        print("Switched to 8888")
    elif port == 5678:
        serverPort = 5678
        sd.bind((serverAddr, serverPort))
        print("Switched to 5678")
    elif port == 5679:
        serverPort = 5679
        sd.bind((serverAddr, serverPort))
        print("Switched to 5679")
    elif port == 5680:
        serverPort = 5680
        sd.bind((serverAddr, serverPort))
        print("Switched to 5680")