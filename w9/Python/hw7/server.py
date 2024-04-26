import socket

f = open('bod.jpg', 'wb')
sd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sd.bind(('127.0.0.1', 1234))

while True:
    data = sd.recv(1024)
    print(f'Received: {data}')
    if not data:
        break  
    if data == b'END':
        break  
    f.write(data)
f.close()
sd.close()