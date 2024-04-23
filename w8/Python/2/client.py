import socket
import time
DATA = [
    "Hello, World!",
    "How are you today?",
    "I'm learning programming.",
    "Python is my favorite language.",
    "Today is a beautiful day.",
    "Coding is fun and challenging.",
    "I enjoy solving problems.",
    "Reading books is a good habit.",
    "Practice makes perfect.",
    "Never stop learning."
]
HOST,PORT = "127.0.0.1",1234
for i in range(10): 
    clientSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    clientSocket.sendto(DATA[i].encode(),(HOST,PORT+i))
    print(f"Message send: {DATA[i]}")
    time.sleep(1)