import socket

FLAG = '~'
ESC = '}'

def stuff(data_str):
    stuffed = ''
    for char in data_str:
        if char == FLAG or char == ESC:
            stuffed += ESC + chr(ord(char) ^ 0x20)
        else:
            stuffed += char
    return stuffed

user_input = input("Enter string: ")
stuffed = stuff(user_input)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 12345))
client.send(stuffed.encode('utf-8'))
client.close()
print("Sent stuffed data.")