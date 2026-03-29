import socket

FLAG = 0x7E
ESC = 0x7D

def stuff(data):
    stuffed = bytearray()
    for byte in data:
        if byte == FLAG or byte == ESC:
            stuffed.append(ESC)
            stuffed.append(byte ^ 0x20)
        else:
            stuffed.append(byte)
    return bytes(stuffed)

user_input = input("Enter string: ")
data = user_input.encode('utf-8')
stuffed = stuff(data)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 12345))
client.send(stuffed)
client.close()
print("Sent stuffed data.")