import socket
import time

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

# Set Non Blocking
sd.setblocking(False)

"""
    File which User want to send/recv
"""
InpurFile = input("Enter file to send data to server: ")
OutputFile = input("Enter file to recv data from server: ")

fin = open(InpurFile, "r")
fout = open(OutputFile, "w")

EOF = False
while True:
    try:
        data = sd.recv(1024).decode()
        print(f"{data}")
        if EOF and data == "END": break
        elif EOF: continue
        fout.write(data)
    except:
        pass
    try:
        data = fin.readline()
        if not data: raise EOFError
        sd.send(data.encode())
        print(f"{data}")
    except EOFError:
        EOF = True
        sd.send(b'END')
        print(f"END")
        break
    time.sleep(1)

    


sd.close()