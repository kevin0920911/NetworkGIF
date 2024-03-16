import socket
import os
def printMeun():
    print("_____________________________________")
    print("|    1. Echo       回應模式          |")
    print("|    2. Discard    丟棄模式          |")
    print("|    3. Daytime    日期與時間模式     |")
    print("|    4. QUOTE      每日一句          |")
    print("|    5. CHARGEN    字元產生器        |")
    print("_____________________________________")

def servicePort(service:int) -> int:
    match service:
        case 1:
            return 7
        case 2:
            return 9
        case 3:
            return 13
        case 4:
            return 17
        case 5:
            return 19
        case _:#Default
            print("Please enter 1~5")
            exit
# Socket set up
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
HOST = "127.0.0.1"
PORT = -1

sendData = ""
recvData = ""

printMeun()
PORT = servicePort(int(input()))
s.connect((HOST, PORT))
if PORT == 7:
    sendData = input("Please enter message u want to send：")
    s.send(sendData.encode()) #Send data by byte
    recvData = s.recv(1024).decode()
if PORT == 9:
    sendData = input("Please enter message u want to send：")
    s.send(sendData.encode()) #Send data by byte
if PORT == 13 or  PORT == 17 or PORT == 19:
    recvData = s.recv(1024).decode('big5')

print("______________執行結果______________")

print(f"[傳送內容]：   {sendData}")
print(f"[傳送內容長度] {len(sendData) + 1} Bytes")


print("____________________________________")
print(f"[回應內容]：   {recvData}")
print(f"[回應內容長度] {len(recvData) + 1} Bytes")

os.system("pause")