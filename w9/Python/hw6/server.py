import socket

f = open('bod.jpg', 'wb')
sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sd.bind(('127.0.0.1', 1234))
sd.listen(1)
conn, addr = sd.accept()

while True:
    data = conn.recv(1024)
    print(f'Received: {data}')
    if not data:
        break  # 如果接收到空資料，表示資料傳輸完成，退出迴圈
    if data == b'END':
        break  # 如果接收到結束標記，表示圖片傳輸完成，退出迴圈
    f.write(data)
f.close()
sd.close()