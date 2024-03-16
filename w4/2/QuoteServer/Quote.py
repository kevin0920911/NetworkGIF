# -*- coding: utf-8 -*-

import socket
import random
QUOTE = [
    "Always code as if the guy who ends up maintaining your code will be a violent psychopath who knows where you live. (Martin Golding)",
    "One man's crappy software is another man's full time job. (Jessica Gaston)",
    "If at first you don't succeed, call it version 1.0 (unknown)",
    "All programmers are playwrights and all computers are lousy actors. (Anonymous Hack Actor)",
    "Any code of your own that you haven't looked at for six or more months might as well have been written by someone else. (Eagleson's law)",
    "Commenting your code is like cleaning your bathroom — you never want to do it, but it really does create a more pleasant experience for you and your guests. (Ryan Campbell)",
    "In order to understand recursion, one must first understand recursion. (Anonymous)",
    "The best thing about a boolean is even if you are wrong, you are only off by a bit.",
    "Should array indices start at 0 or 1? My compromise of 0.5 was rejected without, I thought, proper consideration. (Stan Kelly-Bootle)",
    "Computers are good at following instructions, but not at reading your mind. (Donald Knuth)"
]


HOST = '127.0.0.1'
PORT = 1234

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(5)

print('server start at: %s:%s' % (HOST, PORT))


while True:
    print('wait for connection...')

    conn, addr = s.accept()
    print('connected by ' + str(addr))
    outdata = QUOTE[random.randrange(10)]
    conn.send(outdata.encode())
    conn.close()
    print(f"Server send: {outdata}")
s.close()