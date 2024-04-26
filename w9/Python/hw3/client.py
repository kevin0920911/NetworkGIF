import  socket

DATA = "[NCYU]"
sd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sd.connect(('127.0.0.1',1234))
for i in range(5):
    sd.send(DATA.encode())
    print(f'Sent: {DATA}')
sd.close()