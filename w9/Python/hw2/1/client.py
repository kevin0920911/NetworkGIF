import socket 

DATA = "[NCYU][NCYU][NCYU][NCYU][NCYU]"

sd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sd.connect(('127.0.0.1', 1234))
sd.send(DATA.encode())
print(f'Sent: {DATA}')
sd.close()