import socket
import struct

def string_to_bits(s):
    return ''.join(format(ord(c), '08b') for c in s)

def stuff_bits(bit_str):
    stuffed = ''
    count = 0
    for bit in bit_str:
        stuffed += bit
        if bit == '1':
            count += 1
            if count == 5:
                stuffed += '0'
                count = 0
        else:
            count = 0
    return stuffed

def bits_to_bytes(bits):
    padded = bits + '0' * ((8 - len(bits) % 8) % 8)
    byte_list = []
    for i in range(0, len(padded), 8):
        byte_list.append(int(padded[i:i+8], 2))
    return bytes(byte_list), len(bits)

user_input = input("Enter string: ")
bits = string_to_bits(user_input)
stuffed = stuff_bits(bits)
bytes_data, orig_len = bits_to_bytes(stuffed)
message = struct.pack('I', orig_len) + bytes_data

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 12345))
client.send(message)
client.close()
print("Sent stuffed data.")