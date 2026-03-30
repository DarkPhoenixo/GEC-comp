import socket

FLAG = 0x7E
ESC = 0x7D

def unstuff(data):
    unstuffed = bytearray()
    i = 0
    while i < len(data):
        if data[i] == ESC:
            i += 1
            if i < len(data):
                unstuffed.append(data[i] ^ 0x20)
        else:
            unstuffed.append(data[i])
        i += 1
    return bytes(unstuffed)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12345))
server.listen(1)
print("Server listening on port 12345...")

conn, addr = server.accept()
data = conn.recv(1024)
unstuffed = unstuff(data)
print("Received unstuffed string:", unstuffed.decode('utf-8', errors='ignore'))
conn.close()
server.close()