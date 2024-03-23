import socket
import time

ChargenClient = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
DiscardClient = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

resvData = ""
sendData = ""


"""
    Chargen Server
        IP: 127.0.0.1
        Port: 19
    Discard Server
        IP: 127.0.0.1
        Port: 9
"""
ChargenServerIP   =  "127.0.0.1"
ChargenServerPort =  19
ChargenClient.connect((ChargenServerIP, ChargenServerPort))

DiscardServerIP   =  "127.0.0.1"
DiscardServerPort =  9
DiscardClient.connect((DiscardServerIP,DiscardServerPort))

counter  = 0
byteSent = 0

start = time.time()
while counter<10: 
    resvData = ChargenClient.recv(1024)
    
    bytes = DiscardClient.send(resvData) 
    
    if bytes < 0:
        print("Erro when Send Data to Discard Server")
        exit()
    byteSent += bytes


    #Caluate time
    end = time.time()
    if end - start >= 1:
        print(f"Bytes sent to Discard Server: {byteSent} byte/sec")
        byteSent = 0
        counter += 1
        start = time.time()
DiscardClient.close()
ChargenClient.close()