import socket

"""
Set up Proxy Server information
    Proxy Server
        IP:   127.0.0.1
        Port: 1234
"""
ProxyIP   = '127.0.0.1'
ProxyPort = 1234

"""
Set up Server Information
    DNS Server
        we implement by `gethostbyaddr` funtion
    DateTime Server
        IP:   127.0.0.1
        Port: 13
"""
DateTimeServerIP   = "127.0.0.1"
DateTimeServerPort = 13

"""
Socket setup 
    Server Socket
        For accept client socket
        varible: servsd
    Client Socket
        For Query Date time
        Varible: clintsd
"""
servsd  = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clintsd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


"""
bind Server
"""
servsd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
servsd.bind((ProxyIP, ProxyPort))
servsd.listen(5)

"""
Excute Proxy Server
    1. accept client conntion
    2. resv client want to use which service
    3. send data to server
    4. send data to client
"""
while True:
    print('wait for connection...')
    conn, addr = servsd.accept()
    print('connected by ' + str(addr))
    while True:
        resvData = conn.recv(1024).decode()
        if resvData == "1":
            print("Client Select DNS Query")
            #DNS query
            resvData = list(map(int,(conn.recv(1024).decode()[6:]).split('.')))
            #Enforce data integrity
            if len(resvData) != 4 or not (0<=resvData[0]<=255) or not(0<=resvData[1]<=255) or not(0<=resvData[2]<=255) or not(0<=resvData[3]<=255):
                conn.send("Invalid Data".encode())
                continue
            ip = str(resvData[0]) + "." + str(resvData[1]) + "." + str(resvData[2]) + "." + str(resvData[3])
            hostName = socket.gethostbyaddr(ip)
            if hostName == None:
                print("proxyget: NOTFOUND")
                conn.send("NOTFOUND".encode())
                print("proxysend: NOTFOUND")
            else:
                print(f"proxyget:{str(hostName[0])}")
                conn.send(str(hostName[0]).encode())
                print(f"proxysend:{str(hostName[0])}")
        elif resvData == "2":
            #DateTime Service
            clintsd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            clintsd.connect((DateTimeServerIP,DateTimeServerPort))
            #Remember that, server who sending data use big5 encoding, but decode() use uft8 initiality  
            data = clintsd.recv(1024).decode("big5")
            print(f"proxyget:{data}")
            clintsd.close()
            conn.send(data.encode())
            print(f"proxysend:{data}")
        else:
            #Ivalid Data
            conn.send("Invalid Data".encode())
    print("=====================")
servsd.close()