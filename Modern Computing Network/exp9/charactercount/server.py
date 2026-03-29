import socket

FLAG = '~'
ESC = '}'

def unstuff(stuffed_str):
    unstuffed = ''
    i = 0
    while i < len(stuffed_str):
        if stuffed_str[i] == ESC:
            i += 1
            if i < len(stuffed_str):
                unstuffed += chr(ord(stuffed_str[i]) ^ 0x20)
        else:
            unstuffed += stuffed_str[i]
        i += 1
    return unstuffed

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12345))
server.listen(1)
print("Server listening on port 12345...")

conn, addr = server.accept()
data = conn.recv(1024).decode('utf-8')
unstuffed = unstuff(data)
print("Received unstuffed string:", unstuffed)
conn.close()
server.close()