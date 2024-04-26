import socket

f = open('bod.jpg', 'wb')
sd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sd.bind(('127.0.0.1', 1234))
byte = 0
while True:
    data,addr = sd.recvfrom(1024)
    if addr != ('127.0.0.1', 3456):
        continue
    print(f'Received: {data}')
    if not data:
        break  # 如果接收到空資料，表示資料傳輸完成，退出迴圈
    if data == b'END':
        break  # 如果接收到結束標記，表示圖片傳輸完成，退出迴圈
    f.write(data)
    byte += len(data)
f.close()
if int(sd.recv(1024).decode()) == byte:
    print('File received successfully')
sd.close()