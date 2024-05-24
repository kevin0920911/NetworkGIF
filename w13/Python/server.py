import socket
import time
PORT = [8888, 5678, 5679, 5680]

serversocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serversocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

clientIP, clientPort = "255.255.255.255", 8888
while True:
    # PORT: 8888
    clientPort = PORT[0]
    message = "5678/5679/5680"
    serversocket.sendto(message.encode(), (clientIP, clientPort))
    print(f"Sent to {clientIP}:{clientPort}: {message}")

    # PORT: 5678
    clientPort = PORT[1]
    message = "THIS IS 5678"
    serversocket.sendto(message.encode(), (clientIP, clientPort))
    print(f"Sent to {clientIP}:{clientPort}: {message}")

    # PORT: 5679
    clientPort = PORT[2]
    message = "THIS IS 5679"
    serversocket.sendto(message.encode(), (clientIP, clientPort))
    print(f"Sent to {clientIP}:{clientPort}: {message}")

    # PORT: 5680
    clientPort = PORT[3]
    message = "THIS IS 5680"
    serversocket.sendto(message.encode(), (clientIP, clientPort))
    print(f"Sent to {clientIP}:{clientPort}: {message}")
    
    time.sleep(0.5)
close(serversocket)