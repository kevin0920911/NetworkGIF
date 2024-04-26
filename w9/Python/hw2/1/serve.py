import socket

sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
sd.bind(('127.0.0.1', 1234))
sd.listen(1)
conn, andr = sd.accept()
for i in range(5):
    buffer = conn.recv(6).decode()
    print(f'Received: {buffer}')
    
sd.close()